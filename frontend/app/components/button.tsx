"use client";

import { twMerge } from "tailwind-merge";

export default function Button (props: { text: string, class?: string, f: () => void }) {
    return (
        <button onClick={props.f} className={twMerge("p-3 px-5 bg-neutral-800 rounded-xl flex items-center justify-center ", props.class)}>
            {props.text}
        </button>
    )
}