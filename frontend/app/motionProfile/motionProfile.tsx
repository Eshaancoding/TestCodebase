import { pxlToTiles } from "../components/map";
import { LineProf } from "./line";

export interface Points {
    x: number,             // in pxl format, use pxlToTile
    y: number,             // in pxl format, use pxlToTile
    maxSpeed: number,      // in tiles/sec
    callback: string,
    kp: number,
    lookaheadDist: number  // in tiles
}

function dist (p1: {x: number, y: number}, p2: {x: number, y: number}): number {
    return Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2)) 
}

export function motionProfile (points:Points[], acc:number, numDataPoints:number = 100) {
    let total_time = 0 // in seconds
    let total_dist = 0 // in distance
    let lines : LineProf[] = []

    // create basic lines
    let prev_speed = 0.0
    for (let i = 0; i < points.length - 1; i++) {
        let pointOne = pxlToTiles(points[i].x, points[i].y) 
        let pointTwo = pxlToTiles(points[i+1].x, points[i+1].y) 
        let distance = dist(pointOne, pointTwo)
        let max_speed = points[i].maxSpeed
        let time_sec = distance / max_speed;
        
        total_dist += distance;
        let y_diff = Math.abs(max_speed - prev_speed);

        if (y_diff > 0) {
            lines.push(new LineProf(
                0,
                time_sec,
                max_speed,
                max_speed
            ))            
        } else {
            lines[lines.length - 1].t2 += time_sec
        }
    }

    // if sudden jump in vel, add lines to smooth it
    for (let i = 0; i < lines.length - 1; i++) {
        let diff = Math.abs(lines[i].y2 - lines[i+1].y1)
        if (diff > 0) {
            lines[i].t2 -= diff / (2 * acc);
            lines[i+1].t2 -= diff / (2 * acc);
            lines.splice(i+1, 0, new LineProf(
                0, 
                diff / acc,
                lines[i].y2,
                lines[i+1].y1
            ))
        }
    }

    // add acceleration / decel lines
    let beg_speed = points[0].maxSpeed;
    let end_speed = points[points.length - 1].maxSpeed;

    // acceleration
    lines[0].t2 -= beg_speed / (2 * acc);
    lines.splice(0, 0, new LineProf(
        0,
        beg_speed / acc,
        0,
        beg_speed
    ))

    // deceleration
    lines[lines.length - 1].t2 -= end_speed / (2 * acc)
    lines.push(new LineProf(
        0, 
        end_speed / acc,
        end_speed,
        0
    ))

    // time smooth
    let currentTime = 0
    for (let i = 0; i < lines.length; i++) {
        let w = lines[i].t2 - lines[i].t1
        lines[i].t1 = currentTime
        lines[i].t2 = w + currentTime;
        currentTime += w
    }
    total_time = currentTime

    // get distance and vel data
    let data = []
    let t = 0.0
    while (t <= total_time) {
        let vel = 0.0
        for (let x = 0; x < lines.length; x++) {
            if (t >= lines[x].t1 && t <= lines[x].t2) {
                vel = lines[x].eval(t)
                break;
            }
        }

        data.push({
            "Time": t,
            "Velocity": vel
        }) 

        t += (total_time/numDataPoints)
    }

    // Return
    return {
        "total_time": total_time,
        "total_dist": total_dist,
        "data": data
    }
}