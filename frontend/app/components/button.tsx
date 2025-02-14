"use client";

export default function Button (props: { text: string, class?: string, f: () => void }) {
    return (
        <button onClick={props.f} className={"p-3 px-5 bg-neutral-800 rounded-xl flex items-center content-center " + props.class}>
            {props.text}
        </button>
    )
}