"use client";

import { useState } from "react";
import Button from "./components/button";
import Collapsable from "./components/collapsable";
import Map from "./components/map";
import Prompt from "./components/prompt";

export default function Home() {
  const [paths, setPaths] = useState([] as any[])
  const [pathSelect, setPathSelect] = useState(-1)

  function addPath () {
    setPaths([...paths, {
      "type": "path",
      "points": [],
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
      <div className="grid grid-cols-8 grid-rows-8 gap-4 w-full h-full">
        <div className="col-span-2 row-span-7 p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">
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

        <div className="col-span-4 row-span-7 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl flex justify-center flex-col items-center">
          <Map 
            imageUrl="regularField.png" 
            paths={paths}
            pathSelect={pathSelect}
            setPaths={setPaths}
          />
        </div> 
        <div className="col-span-2 row-span-8 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">

          <Collapsable title="Default Distance Params">
            <Prompt label="Lookahead Distance" unit="tiles" update={(a:string) => console.log(a)} placeholder="0.3" />
            <Prompt label="Max Speed" unit="tile/sec" update={() => console.log("sdf")} placeholder="2.5"/>
            <Prompt label="Max Acceleration" unit="tile/sec^2" update={() => console.log("sdf")} placeholder="12" />
            <Prompt label="KP" unit="" update={() => console.log("sdf")} placeholder="20.42" />
            <Prompt label="End Tolerance" unit="in" update={() => console.log("sdf")} placeholder="0.05"/>
            <Prompt label="Point Tolerance" unit="in" update={() => console.log("sdf")} placeholder="3" />
          </Collapsable>
          
          <Collapsable title="Default Point Turn params">
            <Prompt label="Max Angular Speed" unit="degree/sec" update={() => console.log("sdf")} placeholder="205"/>
            <Prompt label="Max Angular Acceleration" unit="degree/sec^2" update={() => console.log("sdf")} placeholder="400" />
            <Prompt label="KP Angle" unit="" update={() => console.log("sdf")} placeholder="4.62" />
            <Prompt label="Angle Tolerance" unit="deg" update={() => console.log("sdf")} placeholder="0.1"/>
          </Collapsable>

          <Collapsable title="Path Information">
            Stuff
          </Collapsable>
          
        </div>
        <div className="col-span-6 row-span-1 min-w-[300px] p-4 border-neutral-800 w-full h-full border-neutral-700 border-2 rounded-xl">

        </div> 
      </div>
    </div>
  );
}