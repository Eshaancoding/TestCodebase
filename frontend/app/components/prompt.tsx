"use client";

export default function Prompt (props: { label: string, unit: string, placeholder?: string, update: (inp:string) => void }) {
    return (
        <div className="grid grid-col-3 gap-2 items-center my-6 justify-between">
            <p>{props.label}:</p>
            <div className="flex gap-2 items-center">
                <input onChange={(e) => props.update(e.target.value)} placeholder={props.placeholder} className="outline-none bg-neutral-800 p-2 rounded-md w-[150px]" type="number" />
                <p>{props.unit}</p>
            </div>
        </div> 
    )
}