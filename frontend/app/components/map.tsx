"use client";

import React, { useState, useRef, useEffect, useMemo } from "react";
import { Stage, Layer, Image, Circle, Line } from "react-konva";
import useImage from "use-image";

function pxlToTiles (x:number, y:number) {
  return {
    x: (x - 25) * 6 / 725,
    y: 6 - (y - 25.75) * 6 / 725
  }
}

function tileToPxl (x:number, y:number) {
  return {
    x: (x * 725 / 6) + 25,
    y: ((6 - y) * 725 / 6) + 25.75
  }
}

export default function Map (props: { imageUrl: string, paths: any[], pathSelect: number, setPaths: (v:any) => void }) {
  let paths = props.paths;
  let pathSelect = props.pathSelect;
  const [image] = useImage(props.imageUrl);
  const [currentX, setCurrentX] = useState(0)
  const [currentY, setCurrentY] = useState(0)
  const [currentHover, setCurrentHover] = useState(-1)
  const [selected, setIsSelected] = useState(-1)
  const [edit, setIsEdit] = useState(-1)
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

    if (currentHover != -1) {
      if (edit == currentHover) {
        setIsEdit(-1)
      }
      else if (selected == currentHover) {
        setIsEdit(currentHover)
        setIsSelected(-1)
      } else {
        setIsSelected(currentHover)
      }
      return;
    }

    if (pathSelect != -1 && paths[pathSelect]["type"] == "path") {
      let points = paths[pathSelect]["points"].slice()
      points = [...points, {x, y} ]
      let pathsCopy = paths.slice()
      pathsCopy[pathSelect]["points"] = points
      props.setPaths(pathsCopy)
    }
  };

  const handleMouseDown = (e:any) => {
    isDrawing.current = true;
    const pos = e.target.getStage().getPointerPosition();
  };

  const handleMouseMove = (e:any) => {
    const stage = e.target.getStage();
    const point = stage.getPointerPosition();
    const tilePoint = pxlToTiles(point.x, point.y)
    setCurrentX(Math.round(tilePoint.x*1000)/1000)
    setCurrentY(Math.round(tilePoint.y*1000)/1000)

    if (selected != -1) {
      let copy = points.slice()
      copy[selected] = point
      let pathsCopy = paths.slice()
      pathsCopy[pathSelect]["points"] = copy
      props.setPaths(pathsCopy)
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

  const handleMouseUp = () => {
    isDrawing.current = false;
  };

  return (
    <div className="absolute">
      <Stage
        width={775}
        height={775}
        onClick={handleClick}
        onMouseDown={handleMouseDown}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
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
    </div>
  );
};