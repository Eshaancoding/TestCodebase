'use server';

import fs from "fs"
import path from "path";

function tileToPxl (x:number, y:number) {
  return {
    x: (x * 725 / 6) + 25,
    y: ((6 - y) * 725 / 6) + 25.75
  }
}

function parseMove (line:string, lambdaDict: {[key:string]: string}) {
    // get stuff inside params
    let p = line.split("drive.move({")[1]
    p = p.slice(0, p.length - 1); // remove last }
    
    let drivePoints = p.split("DrivePoint(")
    drivePoints = drivePoints.map((value:string) => value.trim())
    drivePoints = drivePoints.filter((value:string) => value.length > 0)
    drivePoints = drivePoints.map((value:string) => value.split("),")[0])
    
    let points = []
    for (var driveP of drivePoints) {
        let [
            x_coords, y_coords, lhd, speed, kp, cb
        ] = driveP.split(",").map((v) => v.trim())
        x_coords = x_coords.slice(1, x_coords.length)
        y_coords = y_coords.slice(0, y_coords.length - 1)
        let x = parseFloat(x_coords.split("_")[0])
        let y = parseFloat(y_coords.split("_")[0])

        points.push({
            x: tileToPxl(x, y).x,
            y: tileToPxl(x, y).y,
            maxSpeed: parseFloat(speed.split("_")[0]),
            callback: cb == "nullopt" ? "" : lambdaDict[cb],
            kp: parseFloat(kp),
            lookaheadDist: parseFloat(lhd.split("_")[0])
        })
    }
    return {
        "type": "path",
        "points": points,
        "display": true
    }
}

function parseLambda (line:string) {
    // get key
    let n = line.split("auto")[1].split("=")[0].trim()
    let v = line.split("[](){")[1].trim() + ";";
    return [n,v]
}

function parseTurn (line:string) {
    let direction = line.includes("Right") ? "Right" : "Left";
    let angle = parseFloat(line.split("drive.turn"+direction+"(")[1].split(")")[0])
    return {
        "type": "turn",
        "direction": direction.toLowerCase(),
        "angle": angle,
        "display": true
    }
}

export default async function readProgram (prog:string) {
    const codebaseDir = path.join(process.cwd(), ".."); // Change filename
    let result = []    
    let lambdaDict : {[key: string]: string} = {} 

    // parse moveParams
    const moveParamsFile = path.join(codebaseDir, "src", "Routes", prog + ".cpp")
    const fileContent = fs.readFileSync(moveParamsFile, "utf-8").toString().trim()
        
    let func = fileContent.split("() {")[1]
    func = func.slice(0, func.length - 1); // remove the last }

    const code = func.split(";")
    for (let i = 0; i < code.length; i++) {
        const line = code[i].trim()
        
        if (line.length <= 1) continue; // skip parsing end of lambda functions
        else if (line.includes("setPos")) continue; // skip setPos statements
        else if (line.includes("drive.move")) result.push(parseMove(line, lambdaDict));
        else if (line.includes("drive.turn")) result.push(parseTurn(line));
        else if (line.includes("[](){")) {
            let [n, v] = parseLambda(line);
            lambdaDict[n] = v
        }
        else {
            result.push({
                "type": "code",
                "code": line + ";"
            })
        }
    }

    return result 
}