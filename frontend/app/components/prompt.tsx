"use client";

// add tooltip later
export default function Prompt (props: { label: string, unit?: string, placeholder?: string, update: (inp:any) => void, isText?: boolean, value?: any }) {
    function onCh (v:any) {
        if (props.isText) {
            props.update(v)
        } else {
            try {
                props.update(parseFloat(v))
            } catch (error:any) {
                props.update(0.0)
            }
        }
    }

    return (
        <div className="grid grid-col-3 gap-2 items-center my-6 justify-between">
            <p className="text-[18px]">{props.label}:</p>
            <div className="flex gap-2 items-center">
                <input value={props.value} onChange={(e) => onCh(e.target.value)} placeholder={props.placeholder} className="outline-none rounded-[7px] bg-neutral-800 p-2 rounded-md w-[150px]" type={props.isText == true ? "text" : "number"} /> 
                <p>{props.unit}</p> 
            </div> 
        </div> 
    )
}