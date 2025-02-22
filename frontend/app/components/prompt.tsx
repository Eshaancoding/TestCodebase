"use client";

import { useState } from "react";

// add tooltip later
export default function Prompt (props: { label: string, unit?: string, placeholder?: string, update: (inp:any) => void, isText?: boolean, value?: any }) {
    let [displayVal, setDisplayVal] = useState(props.value)
    
    function onCh (v:any) {
        setDisplayVal(v) // 
        
        if (props.isText) {
            props.update(v)
        } else {
            try {
                let x = parseFloat(v)
                if (x != undefined && x != null) {
                    props.update(x)
                }
            } catch (error:any) {
                // do nothing
            }
        }
    }

    return (
        <div className="grid grid-col-3 gap-2 items-center my-6 justify-between">
            <p className="text-[18px]">{props.label}:</p>
            <div className="flex gap-2 items-center">
                <input 
                    value={displayVal} 
                    onChange={(e) => onCh(e.target.value)} 
                    placeholder={props.placeholder} 
                    className="outline-none rounded-[7px] bg-neutral-800 p-2 w-[150px]" 
                    type={props.isText == true ? "text" : "number"} 
                /> 
                <p>{props.unit}</p> 
            </div> 
        </div> 
    )
}