import React from 'react';
import "./Button.css";

function Button(params) {
    return <button onClick={params.onClick} className="Button">
    {params.text}
    </button>
}

export default Button;