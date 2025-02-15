"use client";

import { useState } from "react";
import Button from "./components/button";
import Collapsable from "./components/collapsable";
import Map from "./components/map";
import Prompt from "./components/prompt";
import { useAtom } from "jotai";
import { ang_tolerance, def_kp, def_lookhead_dist, def_max_acc, def_max_speed, end_tolerance, kp_angle, max_ang_acc, max_ang_speed, point_tolerance } from "./var";

export default function Home() {
  // yes I am ignoring the entire point of typescript but... I'm in a hurry to complete this
  const [paths, setPaths] = useState([] as any[]) 
  const [pathSelect, setPathSelect] = useState(-1)

  // use atom values
  const [lhd, setLHD] = useAtom(def_lookhead_dist)
  const [ms, setMS] = useAtom(def_max_speed);
  const [ma, setMA] = useAtom(def_max_acc)
  const [kp, setKP] = useAtom(def_kp)
  const [end_tol, setEndTol] = useAtom(end_tolerance)
  const [pt, setPT] = useAtom(point_tolerance)

  const [angAcc, setAngAcc] = useAtom(max_ang_acc)
  const [angSp, setAngSp] = useAtom(max_ang_speed)
  const [kpAng, setKpAng] = useAtom(kp_angle)
  const [angTol, setAngTol] = useAtom(ang_tolerance)

  // helper functions
  function addPath () {
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


  function addTurn () {
    setPaths([...paths, {
      "type": "turn",
      "direction": "left",
      "angle": 90,
      "display": true
    }])
  }

  function addCode () {
    setPaths([...paths, {
      "type": "code",
      "code": "pros::delay(500)"
    }])
  }
  
  function setPathSel (idx: number) { 
    if (pathSelect == idx) setPathSelect(-1)
    else setPathSelect(idx)
  }
  
  function toggleDisplay (idx: number) {
    let d = paths.slice() 
    d[idx]["display"] = !d[idx]["display"]
    setPaths(d)
  }

  function deletePath (idx: number) {
    if (pathSelect == idx) {
      setPathSelect(-1)
    }
    let d = paths.slice()
    d.splice(idx, 1)
    setPaths(d)
  }

  return (
    <div className="absolute items-center justify-items-center min-h-screen font-[family-name:var(--font-geist-sans)] h-full w-full p-4">
      <div className="grid grid-cols-8 gap-4 w-full h-full">
        <div className="col-span-2 p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">
          <div className="flex justify-between mb-8 flex-col gap-2">
            <h1 className="font-bold text-[30px] w-full text-center">Paths</h1>  
            <div className="flex justify-between w-full">
              <Button text="Add Path" f={addPath} />
              <Button text="Add Code" f={addCode} /> 
              <Button text="Add Turn" f={addTurn} /> 
            </div>
          </div>

          <div className="flex gap-4 flex-col">
            {paths.map((element:any, index:number) => {
              if (element["type"] == "path") {
                return (
                  <div key={index} className="flex gap-4">
                    <button 
                      onClick={() => setPathSel(index)} 
                      className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center gap-2 justify-between border-blue-500"
                      style={{
                        borderWidth: pathSelect == index ? "4px" : "0px",
                      }}
                    >
                      <p className="text-[20px]">Path</p>
                      <p>{element["points"].length} points</p>
                    </button>
                    {element['display'] ?
                      <img onClick={() => toggleDisplay(index)} src="eye-off.svg" className="w-[35px] cursor-pointer" />
                    :
                      <img onClick={() => toggleDisplay(index)} src="eye.svg" className="w-[35px] cursor-pointer" />
                    }
                    <img onClick={() => deletePath(index)} src="trash.svg" className="w-[35px] cursor-pointer" />
                  </div>
                )
              } 
              else if (element["type"] == "turn") {
                return (
                  <div key={index} className="flex gap-4">
                    <button 
                      onClick={() => setPathSel(index)} 
                      className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center gap-2 justify-between border-blue-500"
                      style={{
                        borderWidth: pathSelect == index ? "4px" : "0px",
                      }}
                    >
                      <p className="text-[20px]">Turn {element["direction"]} {element["angle"]} deg</p>
                    </button>
                    {element['display'] ?
                      <img onClick={() => toggleDisplay(index)} src="eye-off.svg" className="w-[35px] cursor-pointer" />
                    :
                      <img onClick={() => toggleDisplay(index)} src="eye.svg" className="w-[35px] cursor-pointer" />
                    }
                    <img onClick={() => deletePath(index)} src="trash.svg" className="w-[35px] cursor-pointer" />
                  </div>
                )
              }
              else if (element["type"] == "code") {
                return (
                  <div key={index} className="flex gap-4">
                    <button 
                      onClick={() => setPathSel(index)} 
                      className="bg-neutral-800 w-full rounded-[15px] p-4 flex items-center gap-2 justify-between border-blue-500"
                      style={{
                        borderWidth: pathSelect == index ? "4px" : "0px",
                      }}
                    >
                      <p className="text-[20px]">Code</p>
                      <p className="max-w-[100px] text-neutral-400 text-[14px]">{element["code"]}</p>
                    </button>
                    <img onClick={() => deletePath(index)} src="trash.svg" className="w-[35px] cursor-pointer" />
                  </div>
                )
              }
            })}
          </div>

        </div> 

        <div className="col-span-4 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl flex justify-center flex-col items-center">
          <Map 
            imageUrl="regularField.png" 
            paths={paths}
            pathSelect={pathSelect}
            setPaths={setPaths}
          />
        </div> 
        <div className="col-span-2 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">

          <Collapsable title="Default Distance Params">
            <Prompt label="Lookahead Distance" unit="tiles" update={setLHD} value={lhd} />
            <Prompt label="Max Speed" unit="tile/sec" update={setMS} value={ms} />
            <Prompt label="Max Acceleration" unit="tile/sec^2" update={setMA} value={ma} />
            <Prompt label="KP" unit="" update={setKP} value={kp} />
            <Prompt label="End Tolerance" unit="in" update={setEndTol} value={end_tol} />
            <Prompt label="Point Tolerance" unit="in" update={setPT} value={pt} />
          </Collapsable>
          
          <Collapsable title="Default Point Turn params">
            <Prompt label="Max Angular Speed" unit="degree/sec" update={setAngSp} value={angSp} />
            <Prompt label="Max Angular Acceleration" unit="degree/sec^2" update={setAngAcc} value={angAcc} />
            <Prompt label="KP Angle" unit="" update={setKpAng} value={kpAng} />
            <Prompt label="Angle Tolerance" unit="deg" update={setAngTol} value={angTol} />
          </Collapsable>

          <Collapsable title="Path Information">
            Stuff
          </Collapsable>

          <Collapsable title="Run Program">
            <Prompt label="Program" update={() => console.log("sdf")} isText />
          </Collapsable>
          
        </div>
      </div>
    </div>
  );
}