"use client";

import React, { useState, useRef, useEffect, useMemo, Ref } from "react";
import { Stage, Layer, Image, Circle, Line } from "react-konva";
import useImage from "use-image";
import Prompt from "./prompt";
import { useAtom } from "jotai";
import { def_kp, def_lookhead_dist, def_max_speed, pathsAtom, pathSelectAtom } from "../var";
import Button from "./button";

export function pxlToTiles (x:number, y:number) {
  return {
    x: (x - 25) * 6 / 725,
    y: 6 - (y - 25.75) * 6 / 725
  }
}

export function tileToPxl (x:number, y:number) {
  return {
    x: (x * 725 / 6) + 25,
    y: ((6 - y) * 725 / 6) + 25.75
  }
}

export default function Map (props: { imageUrl: string }) {
  const [paths, setPaths] = useAtom(pathsAtom)
  const [pathSelect, ] = useAtom(pathSelectAtom)

  const [ms, ] = useAtom(def_max_speed);
  const [kp, ] = useAtom(def_kp)
  const [lhd, ] = useAtom(def_lookhead_dist)

  const [image] = useImage(props.imageUrl);
  const [currentX, setCurrentX] = useState(0)
  const [currentY, setCurrentY] = useState(0)
  const [currentHover, setCurrentHover] = useState(-1)
  const [selected, setIsSelected] = useState(-1)
  const [edit, setIsEdit] = useState(-1)
  const stage = useRef(undefined as any)
  const isDrawing = useRef(false);

  useEffect(() => {
    setCurrentHover(-1) // any update in paths will deselect everything
    setIsSelected(-1)
  }, [pathSelect])

  const points = useMemo(() => {
    if (pathSelect != -1 && paths[pathSelect]["type"] == "path") {
      return paths[pathSelect]["points"]
    }
    else {
      return []
    }
  }, [paths, pathSelect])

  const handleClick = (e:any) => {
    const { x, y } = e.target.getStage().getPointerPosition();

    // ensure that we are hovering over point and we are not editing a point currently in move
    if (currentHover != -1 && selected != currentHover && e.evt.button === 2) {
      setIsEdit(currentHover == edit ? -1 : currentHover)
      return;
    }
    else if (e.evt.button == 2) return; // only right click we add point

    // ensure we are hovering over point and we are not editing a point current in edit
    if (currentHover != -1 && edit != currentHover) {
      setIsSelected(currentHover == selected ? -1 : currentHover) 
      return;
    }

    // add point
    if (pathSelect != -1 && paths[pathSelect]["type"] == "path") {
      let points = paths[pathSelect]["points"].slice()
      points = [...points, {
        x: x, 
        y: y,
        maxSpeed: ms,
        callback: "",
        kp: kp,
        lookaheadDist: lhd
      } ]
      let pathsCopy = paths.slice()
      pathsCopy[pathSelect]["points"] = points
      setPaths(pathsCopy)
    }
  };

  const handleMouseMove = (e:any) => {
    const stage = e.target.getStage();
    const point = stage.getPointerPosition();
    const tilePoint = pxlToTiles(point.x, point.y)
    setCurrentX(Math.round(tilePoint.x*1000)/1000)
    setCurrentY(Math.round(tilePoint.y*1000)/1000)

    if (selected != -1) {
      let copy = points.slice()
      copy[selected].x = point.x
      copy[selected].y = point.y
      let pathsCopy = paths.slice()
      pathsCopy[pathSelect]["points"] = copy
      setPaths(pathsCopy)
      return
    }

    const t_point_x = point.x
    const t_point_y = point.y
    let smallestDist = -1; 
    let pointIdx = -1;
    for (let i = 0; i < points.length; i++) {
      let point_x = points[i].x;
      let point_y = points[i].y;
      let dist = Math.sqrt(Math.pow(t_point_x - point_x, 2) + Math.pow(t_point_y - point_y, 2))
      if (dist < smallestDist || smallestDist == -1) {
        pointIdx = i;
        smallestDist = dist;
      }
    }

    if (smallestDist < 15 && pointIdx != -1) { 
      setCurrentHover(pointIdx)
    } else {
      setCurrentHover(-1)
    }
  };

  function setEditPoint (param: string, value:any) {
    let copyPath = paths.slice()
    copyPath[pathSelect]["points"][edit][param] = value
    setPaths(copyPath.slice())
  }

  function deletePoint () {
    let copyPath = paths.slice() 
    let a = []
    copyPath[pathSelect]["points"].splice(edit, 1)
    setIsEdit(-1)
    setIsSelected(-1)
    setCurrentHover(-1)
    setPaths(copyPath)
  }

  stage.current?.on("contextmenu", (e:any) => { e.evt.preventDefault() })

  return (
    <div className="absolute">
      <Stage
        ref={stage}
        width={775}
        height={775}
        onClick={handleClick}
        onMouseMove={handleMouseMove}
        className=""
      >
        <Layer>
          <Image image={image} width={775} height={775} />
          {paths.map((element:any, index:number) => {
            if (element["type"] == "path" && element["display"]) {
              let points = element["points"]
              return (
                <Line 
                  key={index} 
                  points={points.map((val:any) => [val.x, val.y]).flat()} 
                  stroke={(index == pathSelect) ? "blue" : "black"}
                  strokeWidth={2} 
                />
              ) 
            }
          })}          

          {paths.map((element:any, index:number) => {
            if (element["type"] == "path" && element["display"]) {
              let points = element["points"] 
              return points.map((point:any, i:number) => {
                return (
                  <Circle 
                    key={index * 100 + i} 
                    x={point.x} 
                    y={point.y} 
                    radius={((currentHover == i || selected == i) && index == pathSelect) ? 10 : 5} 
                    fill={
                      (edit == i && index == pathSelect) ? "green" : 
                      (selected == i && index == pathSelect) ? "red" : 
                      (index == pathSelect ? "blue" : "black")
                    } 
                  />
                )
              })
            }
          })}

          
        </Layer>
      </Stage>
      <p className="absolute left-0 mt-2 ">Cursor: ({currentX} tile, {currentY} tile)</p>

      {edit != -1 && pathSelect != -1 &&
        <div className="flex flex-col my-8">
          <div className="flex gap-4">
            <Prompt 
              label="Max Speed" 
              unit="tile/sec" 
              update={(v) => setEditPoint("maxSpeed", v)} 
              value={paths[pathSelect]["points"][edit]["maxSpeed"]} 
            />

            <Prompt 
              label="Callback" 
              unit="" 
              update={(v) => setEditPoint("callback", v)} 
              value={paths[pathSelect]["points"][edit]["callback"]} 
              isText 
            />

            <Prompt 
              label="KP" 
              unit="" 
              update={(v) => setEditPoint("kp", v)} 
              value={paths[pathSelect]["points"][edit]["kp"]} 
            />

            <Prompt 
              label="Lookahead Distance" 
              unit="tile" 
              update={(v) => setEditPoint("lookaheadDist", v)} 
              value={paths[pathSelect]["points"][edit]["lookaheadDist"]} 
            />
          </div>
          <Button text="Delete Point" class="bg-red-600 w-[150px] text-center" f={deletePoint} />
        </div>
      }
    </div>
  );
};