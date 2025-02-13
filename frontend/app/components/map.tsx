"use client";

import React, { useState, useRef } from "react";
import { Stage, Layer, Image, Circle, Line } from "react-konva";
import useImage from "use-image";

function pxlToTiles (x:number, y:number) {
  return {
    x: (x - 25) * 6 / 725,
    y: 6 - (y - 25) * 6 / 725
  }
}

export default function Map (props: { imageUrl: string }) {
  const [image] = useImage(props.imageUrl);
  const [points, setPoints] = useState([] as any[]);
  const [lines, setLines] = useState([] as any[]);
  const [currentX, setCurrentX] = useState(0)
  const [currentY, setCurrentY] = useState(0)
  const isDrawing = useRef(false);

  const handleClick = (e:any) => {
    const { x, y } = e.target.getStage().getPointerPosition();
    setPoints([...points, { x, y }]);
  };

  const handleMouseDown = (e:any) => {
    isDrawing.current = true;
    const pos = e.target.getStage().getPointerPosition();
    setLines([...lines, [pos.x, pos.y]]);
  };

  const handleMouseMove = (e:any) => {
    const stage = e.target.getStage();
    const point = stage.getPointerPosition();
    const tilePoint = pxlToTiles(point.x, point.y)
    setCurrentX(Math.round(tilePoint.x*1000)/1000)
    setCurrentY(Math.round(tilePoint.y*1000)/1000)

    if (!isDrawing.current) return;
    let lastLine = lines[lines.length - 1];
    lastLine = [...lastLine, point.x, point.y];
    setLines([...lines.slice(0, -1), lastLine]);
  };

  function handleMouseOver (e:any) {
    const stage = e.target.getStage()
  }

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
        onMouseOver={handleMouseOver}
        className=""
      >
        <Layer>
          <Image image={image} width={775} height={775} />
          {points.map((point, i) => (
            <Circle key={i} x={point.x} y={point.y} radius={5} fill="red" />
          ))}
          {lines.map((line, i) => (
            <Line key={i} points={line} stroke="blue" strokeWidth={2} />
          ))}
        </Layer>
      </Stage>
      <p className="absolute left-0 mt-2 ">Cursor: ({currentX} tile, {currentY} tile)</p>
    </div>
  );
};