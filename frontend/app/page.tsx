"use client";

import Collapsable from "./components/collapsable";
import Map from "./components/map";
import Prompt from "./components/prompt";
import { useAtom } from "jotai";
import { 
  ang_tolerance, 
  p_dist_atom, 
  p_ang_atom,
  def_lookhead_dist, 
  end_tolerance, 
  kp_angle, 
  max_ang_acc, 
  max_ang_speed, 
  point_tolerance,
  ki_angle,
} from "./var";
import getDefValues from "./backend/getDefValues";
import { useEffect, useState } from "react";
import Codebase from "./components/codebase";
import Paths from "./components/Paths";

export default function Home() {
  // use atom values
  const [lhd, setLHD] = useAtom(def_lookhead_dist)
  const [p_dist, set_p_dist] = useAtom(p_dist_atom)
  const [p_ang, set_p_ang] = useAtom(p_ang_atom)
  const [end_tol, setEndTol] = useAtom(end_tolerance)
  const [pt, setPT] = useAtom(point_tolerance)

  // angle
  const [angSp, setAngSp] = useAtom(max_ang_speed)
  const [angAcc, setAngAcc] = useAtom(max_ang_acc)
  const [kpAng, setKpAng] = useAtom(kp_angle)
  const [kiAng, setKiAng] = useAtom(ki_angle)
  const [angTol, setAngTol] = useAtom(ang_tolerance)

  // program
  const [parsed, setParsed] = useState(false)

  useEffect(() => { 
    async function a () {
      let val = await getDefValues()
      let di = val.parsedDictionary
      console.log(di)
      setLHD(di['LOOKAHEAD_DIST'])  
      set_p_dist(di["P_DIST"])
      set_p_ang(di["P_ANG"])
      setEndTol(di["END_TOLERANCE"])
      setPT(di["POINT_TOLERANCE"])

      setAngSp(di["MAX_ANG_SPEED"])
      setAngAcc(di["MAX_ANG_ACCEL"])
      setKpAng(di["KP_ANG"])
      setKiAng(di["KI_ANG"])
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
            <Prompt label="Proportional Distance" unit="" update={set_p_dist} value={p_dist} />
            <Prompt label="Proportional Angle" unit="" update={set_p_ang} value={p_ang} />
            <Prompt label="End Tolerance" unit="in" update={setEndTol} value={end_tol} />
            <Prompt label="Point Tolerance" unit="in" update={setPT} value={pt} />
          </Collapsable>
          
          <Collapsable title="Default Point Turn params">
            <Prompt label="Max Angular Speed" unit="degree/sec" update={setAngSp} value={angSp} />
            <Prompt label="Max Angular Acceleration" unit="degree/sec^2" update={setAngAcc} value={angAcc} />
            <Prompt label="KP Angle" unit="" update={setKpAng} value={kpAng} />
            <Prompt label="KI Angle" unit="" update={setKiAng} value={kiAng} />
            <Prompt label="Angle Tolerance" unit="deg" update={setAngTol} value={angTol} />
          </Collapsable>

          <Collapsable title="Codebase">
            <Codebase /> 
          </Collapsable>
          
        </div>
      </div>
    </div>
  );
}