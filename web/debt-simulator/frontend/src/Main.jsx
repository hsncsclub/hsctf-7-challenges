import React from 'react';
import "./Main.css"

function Main(params) {
    return <div className="Main">
    ${params.content}
    </div>
}

export default Main;