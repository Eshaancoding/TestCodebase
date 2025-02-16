import { useAtom } from "jotai";
import { def_kp, def_lookhead_dist, def_max_speed, pathsAtom, pathSelectAtom } from "../var";
import Button from "./button";

export default function Paths() {
    const [paths, setPaths] = useAtom(pathsAtom)
    const [pathSelect, setPathSelect] = useAtom(pathSelectAtom)
    const [ms, ] = useAtom(def_max_speed)
    const [kp, ] = useAtom(def_kp)
    const [lhd, ] = useAtom(def_lookhead_dist)

    // helper functions
    function addPath() {
        // add point from last path automatically
        let p = [] as any[]
        for (let i = paths.length - 1; i > -1; i--) {
            if (paths[i]["type"] == "path" && paths[i]["points"].length > 0) {
                let points = paths[i]["points"]
                let xPoint = points[points.length - 1].x
                let yPoint = points[points.length - 1].y
                p.push({
                    x: xPoint,
                    y: yPoint,
                    maxSpeed: ms,
                    callback: "",
                    kp: kp,
                    lookaheadDist: lhd
                })
                break
            }
        }
        setPaths([...paths, {
            "type": "path",
            "points": p,
            "display": true
        }])
    }


    function addTurn() {
        setPaths([...paths, {
            "type": "turn",
            "direction": "left",
            "angle": 90,
            "display": true
        }])
    }

    function addCode() {
        setPaths([...paths, {
            "type": "code",
            "code": "pros::delay(500);"
        }])
    }

    function setPathSel(idx: number) {
        if (pathSelect == idx) setPathSelect(-1)
        else setPathSelect(idx)
    }

    function toggleDisplay(idx: number) {
        let d = paths.slice()
        d[idx]["display"] = !d[idx]["display"]
        setPaths(d)
    }

    function deletePath(idx: number) {
        if (pathSelect == idx) {
            setPathSelect(-1)
        }
        let d = paths.slice()
        d.splice(idx, 1)
        setPaths(d)
    }

    function setCode(idx: number, code: string) {
        let d = paths.slice()
        d[idx]["code"] = code
        setPaths(d)
    }

    function setAngle(idx: number, angle: string) {
        let d = paths.slice()
        try {
            let ang = parseFloat(angle)
            if (ang < 0) {
                d[idx]["direction"] = d[idx]["direction"] == "left" ? "right" : "left"
            }
            d[idx]["angle"] = Math.abs(ang) % 180
            setPaths(d)
        } catch (e: any) {
        }
    }

    function goUp(idx: number) {
        if (idx > 0) {
            let d = paths.slice()
            let v = d.splice(idx, 1)
            d.splice(idx - 1, 0, v[0])
            setPaths(d)
        }
    }

    function goDown(idx: number) {
        if (idx < paths.length - 1) {
            let d = paths.slice()
            let v = d.splice(idx, 1)
            d.splice(idx + 1, 0, v[0])
            setPaths(d)
        }
    }

    return (
        <>
            <div className="flex justify-between mb-8 flex-col gap-2">
                <h1 className="font-bold text-[30px] w-full text-center">Paths</h1>
                <div className="flex justify-between w-full">
                    <Button text="Add Path" f={addPath} />
                    <Button text="Add Code" f={addCode} />
                    <Button text="Add Turn" f={addTurn} />
                </div>
            </div>

            <div className="flex gap-4 flex-col">
                {paths.map((element: any, index: number) => {
                    if (element["type"] == "path") {
                        return (
                            <div key={index} className="flex gap-2">
                                <button
                                    onClick={() => setPathSel(index)}
                                    className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center gap-2 justify-between border-blue-500 mr-2"
                                    style={{
                                        borderWidth: pathSelect == index ? "4px" : "0px",
                                    }}
                                >
                                    <p className="text-[20px]">Path</p>
                                    <p>{element["points"].length} points</p>
                                </button>
                                {element['display'] ?
                                    <img onClick={() => toggleDisplay(index)} src="eye-off.svg" className="w-[30px] cursor-pointer" />
                                    :
                                    <img onClick={() => toggleDisplay(index)} src="eye.svg" className="w-[30px] cursor-pointer" />
                                }
                                <img onClick={() => goDown(index)} src="angle-down.svg" className="w-[30px] cursor-pointer" />
                                <img onClick={() => goUp(index)} src="angle-down.svg" className="rotate-180 w-[30px] cursor-pointer" />
                                <img onClick={() => deletePath(index)} src="trash.svg" className="w-[30px] cursor-pointer" />
                            </div>
                        )
                    }
                    else if (element["type"] == "turn") {
                        return (
                            <div key={index} className="flex gap-2">
                                <button
                                    onClick={() => setPathSel(-1)}
                                    className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center justify-between border-blue-500 mr-2"
                                    style={{
                                        borderWidth: pathSelect == index ? "4px" : "0px",
                                    }}
                                >
                                    <p className="text-[20px] text-left w-[100px]">Turn {element["direction"]}</p>
                                    <div className="flex items-center">
                                        <input
                                            value={element["angle"]}
                                            onChange={(e) => setAngle(index, e.target.value)}
                                            className="w-[100px] text-right outline-none bg-neutral-800 p-2 rounded-md text-right"
                                            type="number"
                                            placeholder="90"
                                        />
                                        <p>deg</p>
                                    </div>
                                </button>
                                {/* {element['display'] ?
                      <img onClick={() => toggleDisplay(index)} src="eye-off.svg" className="w-[30px] cursor-pointer" />
                    :
                      <img onClick={() => toggleDisplay(index)} src="eye.svg" className="w-[30px] cursor-pointer" />
                    } */}
                                <img onClick={() => goDown(index)} src="angle-down.svg" className="w-[30px] cursor-pointer" />
                                <img onClick={() => goUp(index)} src="angle-down.svg" className="rotate-180 w-[30px] cursor-pointer" />
                                <img onClick={() => deletePath(index)} src="trash.svg" className="w-[30px] cursor-pointer" />
                            </div>
                        )
                    }
                    else if (element["type"] == "code") {
                        return (
                            <div key={index} className="flex gap-2">
                                <button
                                    onClick={() => setPathSel(-1)}
                                    className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center justify-between border-blue-500 mr-2"
                                    style={{
                                        borderWidth: pathSelect == index ? "4px" : "0px",
                                    }}
                                >
                                    <p className="text-[20px]">Code</p>
                                    <input
                                        value={element["code"]}
                                        onChange={(e) => setCode(index, e.target.value)}
                                        className="w-[200px] outline-none bg-neutral-800 p-2 rounded-md text-right"
                                        type="text"
                                        placeholder="Enter Code Here"
                                    />
                                </button>
                                <img onClick={() => goDown(index)} src="angle-down.svg" className="w-[30px] cursor-pointer" />
                                <img onClick={() => goUp(index)} src="angle-down.svg" className="rotate-180 w-[30px] cursor-pointer" />
                                <img onClick={() => deletePath(index)} src="trash.svg" className="w-[30px] cursor-pointer" />
                            </div>
                        )
                    }
                })}
            </div>
        </>
    )
}