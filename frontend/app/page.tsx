"use client";

import Collapsable from "./components/collapsable";
import Map from "./components/map";
import Prompt from "./components/prompt";
import { useAtom } from "jotai";
import { ang_tolerance, def_kp, def_lookhead_dist, def_max_acc, def_max_speed, end_tolerance, ki_atom, kp_angle, max_ang_acc, max_ang_speed, pathsAtom, pathSelectAtom, point_tolerance } from "./var";
import PathInfo from "./components/PathInfo";
import getDefValues from "./backend/getDefValues";
import { useEffect, useState } from "react";
import Codebase from "./components/Codebase";
import Paths from "./components/Paths";

export default function Home() {
  // yes I am ignoring the entire point of typescript but... I'm in a hurry to complete this
  const [paths, setPaths] = useAtom(pathsAtom)
  const [pathSelect, setPathSelect] = useAtom(pathSelectAtom)

  // use atom values
  const [lhd, setLHD] = useAtom(def_lookhead_dist)
  const [ms, setMS] = useAtom(def_max_speed);
  const [ma, setMA] = useAtom(def_max_acc)
  const [kp, setKP] = useAtom(def_kp)
  const [ki, setKI] = useAtom(ki_atom)
  const [end_tol, setEndTol] = useAtom(end_tolerance)
  const [pt, setPT] = useAtom(point_tolerance)

  const [angAcc, setAngAcc] = useAtom(max_ang_acc)
  const [angSp, setAngSp] = useAtom(max_ang_speed)
  const [kpAng, setKpAng] = useAtom(kp_angle)
  const [angTol, setAngTol] = useAtom(ang_tolerance)

  // program
  const [parsed, setParsed] = useState(false)

  useEffect(() => { 
    async function a () {
      let val = await getDefValues()
      let di = val.parsedDictionary
      setLHD(di['LOOKAHEAD_DIST'])  
      setMS(di['MAX_SPEED'])
      setMA(di['MAX_ACCEL'])
      setKP(di["KP"])
      setKI(di["KI"])
      setEndTol(di["END_TOLERANCE"])
      setPT(di["POINT_TOLERANCE"])
      setAngAcc(di["MAX_ANG_ACCEL"])
      setAngSp(di["MAX_ANG_SPEED"])
      setAngTol(di["ANG_TOLERANCE"])
      setParsed(true)
    }
    if (!parsed) {
      a()
    }
  }, [])

  

  return (
    <div className="absolute items-center justify-items-center min-h-screen font-[family-name:var(--font-geist-sans)] h-full w-full p-4">
      <div className="grid grid-cols-8 gap-4 w-full h-full">
        <div className="col-span-2 p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">
          <Paths /> 
        </div> 

        <div className="col-span-4 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl flex justify-center flex-col items-center">
          <Map />
        </div> 
        <div className="col-span-2 min-w-[300px] p-4 border-neutral-700 w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">

          <Collapsable title="Default Distance Params">
            <Prompt label="Lookahead Distance" unit="tiles" update={setLHD} value={lhd} />
            <Prompt label="Max Speed" unit="tile/sec" update={setMS} value={ms} />
            <Prompt label="Max Acceleration" unit="tile/sec^2" update={setMA} value={ma} />
            <Prompt label="KP" unit="" update={setKP} value={kp} />
            <Prompt label="KI" unit="" update={setKI} value={ki} />
            <Prompt label="End Tolerance" unit="in" update={setEndTol} value={end_tol} />
            <Prompt label="Point Tolerance" unit="in" update={setPT} value={pt} />
          </Collapsable>
          
          <Collapsable title="Default Point Turn params">
            <Prompt label="Max Angular Speed" unit="degree/sec" update={setAngSp} value={angSp} />
            <Prompt label="Max Angular Acceleration" unit="degree/sec^2" update={setAngAcc} value={angAcc} />
            <Prompt label="KP Angle" unit="" update={setKpAng} value={kpAng} />
            <Prompt label="Angle Tolerance" unit="deg" update={setAngTol} value={angTol} />
          </Collapsable>

          <Collapsable title="Motion Profile">
            {(pathSelect != -1 && paths[pathSelect]["type"] == "path" && paths[pathSelect]["points"].length > 1) ? 
              <PathInfo />               
            :
              <p>No path selected</p>
            }
          </Collapsable>

          <Collapsable title="Codebase">
            <Codebase /> 
          </Collapsable>
          
        </div>
      </div>
    </div>
  );
}