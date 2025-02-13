"use client";

export default function Button (props: { text: string, class?: string, f: () => void }) {
    return (
        <button onClick={props.f} className={"p-2 px-4 bg-blue-700 rounded-xl flex items-center content-center " + props.class}>
            {props.text}
        </button>
    )
}