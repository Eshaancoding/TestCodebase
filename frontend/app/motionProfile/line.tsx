// word for word translated from motionProfiling.h

export class LineProf {
    t1: number; // in seconds
    t2: number;
    y1: number; // in tiles / sec
    y2: number;
    slope: number; // tiles / sec^2
    intercept: number; // tiles / sec
    
    constructor (t1:number, t2:number, y1:number, y2:number) {
        this.t1 = t1;
        this.t2 = t2;
        this.y1 = y1;
        this.y2 = y2;

        this.slope = (this.y2 - this.y1) / (this.t2 - this.t1);
        this.intercept = (this.y2 - this.slope * this.t2);
    }

    eval (t: number): number {
        if (t < this.t1 || t > this.t2) return 0.0
        return this.slope * (t - this.t1) + this.y1;
    }

    // this is the integral of: INT (y + bx) dx line with bounds t1 - t
    // if t is out of bounds then it will be set to t2 (full area included)
    area (tUn: number): number {
        let t = tUn
        if (tUn < this.t1) return 0.0
        if (tUn > this.t2) t = this.t2;

        let t_sq = Math.pow(t, 2)
        let t1_sq = Math.pow(this.t1, 2);

        return ((this.slope / 2) * (t_sq - t1_sq)) + this.intercept * (t - this.t1)
    }
}