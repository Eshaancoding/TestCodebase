import { atom } from "jotai";

// yes I am ignoring the entire point of typescript but... I'm in a hurry to complete this
export const pathsAtom = atom([] as any[])
export const pathSelectAtom = atom(-1)

export const def_lookhead_dist = atom(0.3);
export const p_dist_atom = atom(10.42)
export const p_ang_atom = atom(5.3)
export const end_tolerance = atom(0.05)
export const point_tolerance = atom(3)

// angle is fine
export const max_ang_speed = atom(205);
export const max_ang_acc = atom(400)
export const kp_angle = atom(3.42)
export const ki_angle = atom(7.32)
export const ang_tolerance = atom(0.1)

export const is_skills = atom(false);