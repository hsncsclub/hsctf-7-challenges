import React from 'react';
import "./Message.css";

function Message(params) {
    return <div className="Message">
    {params.message}
    </div>
}

export default Message;