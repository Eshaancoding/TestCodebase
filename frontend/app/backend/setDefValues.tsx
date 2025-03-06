'use server';

import fs from "fs";
import path from "path";

interface inpTy {
    param_name:string,
    value:number,
    units:string|undefined
}

export default async function setDefValues (inp:inpTy[]) {
    const codebaseDir = path.join(process.cwd(), "..") 
    const moveParamsFile = path.join(codebaseDir, "include", "moveParams.h")
    const fileContent = fs.readFileSync(moveParamsFile, "utf-8").toString().trim()
    const lines = fileContent.split("\n")

    let toWrite = "" 
    
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i]
        let isFound = false
        for (let x of inp) {
            const param_name = x.param_name
            const value = x.value 
            const units = x.units
            if (line.includes("#define") && line.includes(param_name)) {
                isFound = true
                let splitLine = line.split(" ");
                let idx = 0
                for (let l of splitLine) {
                    if (units == undefined && !isNaN(parseFloat(l))) {
                        splitLine[idx] = value.toString()
                        break
                    }
                    else if (l.includes("_") && !isNaN(parseFloat(l.split("_")[0].trim()))) {
                        splitLine[idx] = value.toString() + "_" + units;
                        break
                    }
                    idx += 1; 
                }

                toWrite += splitLine.join(" ") + "\n";
                break
            }
        }
        
        if (!isFound) {
            toWrite += line + "\n";
        }
    }

    console.log(toWrite)
    fs.writeFileSync(moveParamsFile, toWrite, "utf-8")
}