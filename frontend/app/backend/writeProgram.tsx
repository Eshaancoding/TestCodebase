'use server';

import fs from "fs"
import path from "path";

function pxlToTiles (x:number, y:number) {
  return {
    x: (x - 25) * 6 / 725,
    y: 6 - (y - 25.75) * 6 / 725
  }
}

function r (x:number) {
    return Math.round(x*10000)/10000
}

export default async function writeProgram (prog:string, paths:any[]) {
    let resultCode = ""
    const codebaseDir = path.join(process.cwd(), ".."); // Change filename
    const moveParamsFile = path.join(codebaseDir, "src", "Routes", prog + ".cpp")
    const fileContent = fs.readFileSync(moveParamsFile, "utf-8").toString().trim()

    let lambdaCounter = 1;
    let preFile = fileContent.split("() {")[0]
    
    for (var p of paths) {
        if (p["type"] == "turn") {
            let dir = p["direction"] == "right" ? "Right" : "Left"
            resultCode += "\tdrive.turn" + dir + "(" + p["angle"].toString() + "_deg);\n\n"
        } 
        else if (p["type"] == "path") {
            /*
            drive.move({
                DrivePoint({0_tile, 0_tile}, 0.3_tile, 0.2_tps, 20.32, nullopt),
                DrivePoint({0_tile, 3_tile}, 0.3_tile, 0.5_tps, 20.32, nullopt),
                DrivePoint({1_tile, 3_tile}, 0.3_tile, 0.3_tps, 20.32, nullopt),
            });
            */
            let m = "";
            let lambdaFuncs = "";

            m += "drive.move({\n";
            for (var point of p["points"]) {
                m += "\t\tDrivePoint({" + r(pxlToTiles(point['x'], point['y']).x).toString() + "_tile, ";
                m += r(pxlToTiles(point['x'], point['y']).y).toString() + "_tile}, ";
                m += point["lookaheadDist"].toString() + "_tile, ";
                m += point["maxSpeed"].toString() + "_tps, ";
                m += point["kp"].toString() + ", ";
                if (point["callback"].length > 0) {
                    lambdaFuncs += "\tauto lambda" + lambdaCounter.toString() + " = [](){ " + point["callback"] + " };\n";
                    m += "lambda" + lambdaCounter.toString();
                    lambdaCounter += 1;
                } else {
                    m += "nullopt";
                }
                m += "),\n";
            }
            m += "\t});"

            resultCode += lambdaFuncs + "\n\t" + m + "\n\n";
        } 
        else if (p["type"] == "code") {
            resultCode += "\t" + p["code"] + "\n\n";
        }
    }

    let totalFile = preFile + "() {\n" + resultCode + "\n}";

    fs.writeFileSync(moveParamsFile, totalFile, "utf-8");

    console.log(totalFile)
}