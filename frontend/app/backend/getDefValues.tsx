'use server';

import fs from "fs"
import path from "path";

export default async function getDefValues () {
    const codebaseDir = path.join(__dirname, "..", "..", "..", ".."); // Change filename

    let parsedDictionary = {} as any

    // parse moveParams
    const moveParamsFile = path.join(codebaseDir, "include", "moveParams.h")
    console.log(moveParamsFile)
    const fileContent = fs.readFileSync(moveParamsFile, "utf-8").toString().trim()
    const lines = fileContent.split("\n")
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i]
        if (line.includes("#define")) {
            let st = line.trim().split(" ")
            let idx = 0
            while (idx < st.length) {
                if (st[idx].length == 0) {
                    st.splice(idx, 1)
                } else {
                    idx += 1
                }
            }
            const name = st[1]
            let value = st[2]
            if (value.includes("_")) value = value.split("_")[0]
            let parsedVal = parseFloat(value)
            parsedDictionary[name] = parsedVal
        }
    }

    return {
        parsedDictionary: parsedDictionary
    };
}