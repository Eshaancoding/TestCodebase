import { useEffect, useState } from "react";
import Button from "./button";
import Prompt from "./prompt";
import { useAtom } from "jotai";
import { pathsAtom, pathSelectAtom } from "../var";
import writeProgram from "../backend/writeProgram";
import readProgram from "../backend/readProgram";
import { isRunning as ProgRunning, returnText, startProgram, stopProgram } from "../backend/runProgram";


export default function Codebase () {
    const [program, setProgram] = useState("")
    const [paths, setPaths] = useAtom(pathsAtom)
    const [, setPathSelect] = useAtom(pathSelectAtom)
    const [out, setOut] = useState("")
    const [isRun, setIsRunning] = useState(false)
    const [currentInterval, setCurrentInterval] = useState(undefined as NodeJS.Timeout | undefined)
    
    async function run () {
        setIsRunning(true)
        writeProgram(program, paths) 
        startProgram()

        const id = setInterval(async () => {
            setOut(await returnText())

            let prog_run = await ProgRunning()
            if (!prog_run) await stop()
        }, 200)
        setCurrentInterval(id)
    }

    async function stop () {
        clearInterval(currentInterval)
        setCurrentInterval(undefined)
        setIsRunning(false)
        stopProgram()
    }

    useEffect(() => {
    return () => {
      if (currentInterval != undefined) {
        clearInterval(currentInterval);
      }
    };
  }, [currentInterval]);

    return (
        <div className="flex flex-col gap-4">
            <div className="flex flex-row gap-6">
                <Prompt label="Program" update={setProgram} isText />
            </div>
            <div className="flex justify-center gap-4" >
                {!isRun ?
                    <Button text="Run" class="w-[100px] bg-blue-500" f={run} />
                :
                    <Button text="Stop" class="w-[100px] bg-red-500" f={stop} />
                }
                <Button text="Save" class="w-[100px]" f={() => writeProgram(program, paths)} />
                <Button text="Parse" class="w-[100px]" f={async () => { setPaths(await readProgram(program)); setPathSelect(-1) } } />
            </div>
            <div className="w-full bg-neutral-800 p-4 rounded-[15px] flex flex-col">
                <p className="font-bold text-[20px]">Terminal Output:</p>
                {out.split("\n").map((value:string, index:number) => {
                    return ( 
                        <p key={index} className="text-[14px]">{value}</p>
                    )
                })}
            </div>
        </div>
    )    
}