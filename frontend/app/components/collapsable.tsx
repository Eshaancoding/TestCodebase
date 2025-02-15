"use client";
import { useState } from 'react';

export default function Collapsable (props: { title: string, children: any }) {
    const [isOpen, setIsOpen] = useState(false)
    return (
        <div>
            <div className="flex items-center">
                {isOpen ? 
                    <img src="angle-down.svg" color="white" className='w-[35px] h-[35px] cursor-pointer' onClick={() => setIsOpen(!isOpen)} /> :
                    <img src="angle-right.svg" color="white" className='w-[35px] h-[35px] cursor-pointer' onClick={() => setIsOpen(!isOpen)} />
                }
                <h1 className="font-bold text-[20px] my-6 w-full text-center">{props.title}</h1>  
            </div>
            <div style={{display: isOpen ? "block" : "none" }}>
                {props.children}
            </div>
        </div>
    )

}