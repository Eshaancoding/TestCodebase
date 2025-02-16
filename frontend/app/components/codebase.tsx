import { useEffect, useState } from "react";
import Button from "./button";
import Prompt from "./prompt";
import { useAtom } from "jotai";
import { is_skills, pathsAtom, pathSelectAtom } from "../var";
import writeProgram from "../backend/writeProgram";
import readProgram from "../backend/readProgram";
import { isRunning as ProgRunning, returnText, startProgram, stopProgram } from "../backend/Program";
import getPrograms from "../backend/getPrograms";

export default function Codebase () {
    const [program, setProgram] = useState("")
    const [paths, setPaths] = useAtom(pathsAtom)
    const [, setPathSelect] = useAtom(pathSelectAtom)
    const [out, setOut] = useState("")
    const [isRun, setIsRunning] = useState(false)
    const [currentInterval, setCurrentInterval] = useState(undefined as NodeJS.Timeout | undefined)
    const [availableFiles, setAvailableFiles] = useState([] as string[])
    const [, setIsSkills] = useAtom(is_skills)
    
    const [initAngle, setInitAngle] = useState(90)
    
    useEffect(() => {
        async function a () {
            setAvailableFiles(await getPrograms())
        }
        a()
    }, [])
    
    async function run () {
        if (program.length == 0) return
        setOut("")
        setIsRunning(true)
        writeProgram(program, paths, initAngle) 
        startProgram()

        const id = setInterval(async () => {
            let prog_run = await ProgRunning()
            if (!prog_run) { await stop() }
            else { setOut(await returnText()) }
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

    async function setP (file:string) {
        if (program == file) {
            setProgram("")
        }
        else {
            if (file.includes("skill")) {
                setIsSkills(true)
            } 
            else {
                setIsSkills(false)
            }
            
            setProgram(file)
            let d = await readProgram(file)
            setPaths(d.result)
            setInitAngle(d.initAngle) 
        }
    }

    return (
        <div className="flex flex-col gap-4">
            <Prompt label="Initial Angle" unit="deg" value={initAngle} update={setInitAngle} />
            <p>Select a program:</p>
            <div className="grid grid-cols-3 gap-6 mb-4">
                {availableFiles.map((file:string, index:number) => {
                    return (
                        <button 
                            key={index} 
                            onClick={() => setP(file)} 
                            className={`p-2 rounded-xl text-center ${program == file ? 'bg-neutral-600' : 'bg-neutral-800'}`}
                        >
                            {file}
                        </button>
                    )
                })}
            </div>
            <p className="w-full text-center">Commands:</p>
            <div className="flex justify-center gap-4" >
                {!isRun ?
                    <Button text="Run" class="w-[100px] bg-blue-500" f={run} />
                :
                    <Button text="Stop" class="w-[100px] bg-red-500" f={stop} />
                }
                <Button text="Save" class="w-[100px]" f={() => writeProgram(program, paths, initAngle)} />
            </div>
            {(isRun || out.length > 0) && 
                <div className="w-full bg-neutral-800 p-4 rounded-[15px] flex flex-col gap-1">
                    <p className="font-bold text-[20px]">Terminal Output:</p>
                    {out.length > 0 ?
                        out.split("\n").map((value:string, index:number) => {
                            return ( 
                                <p key={index} className="text-[14px]">{value}</p>
                            )
                        })
                    :
                        <p>Running...</p>
                    }
                </div>
            }
        </div>
    )    
}