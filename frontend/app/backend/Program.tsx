'use server';

import { ChildProcessWithoutNullStreams, spawn } from "child_process";

let process:ChildProcessWithoutNullStreams | undefined = undefined
let t = ""
let isRun = false

export async function startProgram () {
    if (!isRun) {
        process = spawn("pros", ["mut"]);
        isRun = true
        process.stdout.on("data", (data) => {
            t = t + "\n" + data.toString(); // Send each chunk of output
        });

        process.stderr.on("data", (data) => {
            t = t + "\n" + data.toString(); // Send errors if any
        });

        process.on("close", (code) => {
            t = t + "\n" + `Process exited with code ${code}`;
            isRun = false
        });
    }
}

export async function returnText () {
    return t
}

export async function isRunning () {
    return isRun
}

export async function stopProgram () {
    console.log("stopped program")
    if (isRun) {
        process?.kill("SIGKILL")
        process?.disconnect()
    }
    isRun = false
}