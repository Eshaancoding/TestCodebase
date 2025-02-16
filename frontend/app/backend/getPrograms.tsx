'use server';

import fs from "fs"
import path from "path";

export default async function getPrograms () {
    const codebaseDir = path.join(process.cwd(), ".."); // Change filename
    const files = path.join(codebaseDir, "src", "Routes");
    let actualFiles = fs.readdirSync(files)
    actualFiles = actualFiles.map((v:string) => v.split(".cpp")[0].trim()) 
    return actualFiles
}