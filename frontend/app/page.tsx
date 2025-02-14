"use client";

import Button from "./components/button";
import Collapsable from "./components/collapsable";
import Map from "./components/map";
import Prompt from "./components/prompt";

export default function Home() {
  return (
      <div className="absolute items-center justify-items-center min-h-screen font-[family-name:var(--font-geist-sans)] h-full w-full p-4">
        <div className="grid grid-cols-8 grid-rows-8 gap-4 w-full h-full">
          <div className="col-span-2 row-span-7 p-4 border-white w-full h-full border-neutral-800 border-2 rounded-xl">
            <div className="flex justify-between">
              <h1 className="font-bold text-[30px]">Paths</h1>  
                <div className="flex gap-4">
                  <Button text="Add Path" f={() => console.log("pressed")} />
                  <Button text="Add Code" f={() => console.log("pressed")} />
                </div>
            </div>
          </div> 
          <div className="col-span-4 row-span-7 min-w-[300px] p-4 border-white w-full h-full border-neutral-800 border-2 rounded-xl flex justify-center flex-col items-center">
            <Map imageUrl="regularField.png" />
          </div> 
          <div className="col-span-2 row-span-8 min-w-[300px] p-4 border-white w-full h-full border-neutral-800 border-2 rounded-xl overflow-y-auto">
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
          <div className="col-span-6 row-span-1 min-w-[300px] p-4 border-neutral-800 w-full h-full border-white border-2 rounded-xl">

          </div> 
        </div>
      </div>
  );
}

/*
#define MAX_ANG_SPEED   205_dps         // degree per second
#define MAX_ANG_ACCEL   400_dps2        // degree per second squared  
#define KP_ANG          4.62         // P parameter between current angle and target angle from motion profiling
#define ANG_TOLERANCE   0.1_deg         // angle tolerance before quitting tolerance
*/