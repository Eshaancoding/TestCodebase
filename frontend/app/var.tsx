import { atom } from "jotai";

// yes I am ignoring the entire point of typescript but... I'm in a hurry to complete this
export const pathsAtom = atom([] as any[])
export const pathSelectAtom = atom(-1)

export const def_lookhead_dist = atom(0.3);
export const def_max_speed = atom(2.5)
export const def_max_acc = atom(12)
export const def_kp = atom(20.42)
export const ki_atom = atom(5.02)
export const end_tolerance = atom(0.05)
export const point_tolerance = atom(3)

export const max_ang_speed = atom(205);
export const max_ang_acc = atom(400)
export const kp_angle = atom(4.62)
export const ang_tolerance = atom(0.1)

export const initial_angle = atom(90) // in degree
export const is_skills = atom(false);