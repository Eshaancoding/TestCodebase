"use client";

import React, { useState, useRef } from "react";
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

export default function Map (props: { imageUrl: string }) {
  const [image] = useImage(props.imageUrl);
  const [points, setPoints] = useState([] as any[]);
  const [currentX, setCurrentX] = useState(0)
  const [currentY, setCurrentY] = useState(0)
  const [currentHover, setCurrentHover] = useState(-1)
  const [selected, setIsSelected] = useState(-1)
  const isDrawing = useRef(false);

  const handleClick = (e:any) => {
    const { x, y } = e.target.getStage().getPointerPosition();
       

    if (currentHover != -1) {
      setIsSelected(selected == currentHover ? -1 : currentHover)
      return;
    }

    setPoints([...points, { x, y }]);
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
      setPoints(copy)
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
          <Line key={2} points={points.map((val) => [val.x, val.y]).flat()} stroke="blue" strokeWidth={2} />
          {points.map((point, i) => (
            <Circle key={i} x={point.x} y={point.y} radius={(currentHover == i || selected == i) ? 10 : 5} fill={selected == i ? "blue" : "red"} />
          ))}
        </Layer>
      </Stage>
      <p className="absolute left-0 mt-2 ">Cursor: ({currentX} tile, {currentY} tile)</p>
    </div>
  );
};