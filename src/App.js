import React, { useState, useEffect } from 'react';
import Header from "./Header";
import Main from './Main';
import Message from './Message';
import Button from "./Button";
import "./App.css";

function App() {
  const [message, setMessage] = useState("Ready to Play?");
  const [runningTotal, setRunningTotal] = useState(0);
  const [buttonText, setButtonText] = useState("Start Game");


  useEffect(() => {
    if (runningTotal < -1000) {
      setMessage("You lost. You have less than $-1000. Better luck next time.");
      setButtonText("Play Again");
    } else if (runningTotal > 2000) {
      setMessage("You won. You have more than $2000. Try your luck again?");
      setButtonText("Play Again");
    } else if (runningTotal !== 0 && buttonText !== "Next Round") {
      setButtonText("Next Round");
    }
  }); 

  const onClick = () => {
    const isGetCost = Math.random() > 0.4 ? true : false;
    const func = isGetCost ? 'getCost' : 'getPay';
    const requestOptions = {
      method: 'POST',
      body: 'function=' + func,
      headers: { 'Content-type': 'application/x-www-form-urlencoded' }
    }

    fetch("https://mighty-reef-57944.herokuapp.com/yolo_0000000000001", requestOptions)
    .then(res => res.json())
    .then(data => {
      data = data.response;
      if (buttonText === "Play Again" || buttonText === "Start Game") {
        setButtonText("Next Round");
        setRunningTotal(0);
      }
      setMessage("You have " + (isGetCost ? "paid me " : "received ") + "$" + data + ".");
      setRunningTotal(runningTotal => isGetCost ? runningTotal - data : runningTotal + data);
    });
  }

  return <div className="App">
    <Header />
    <Message message={message}/>
    <Main content={runningTotal}/>
    <Button onClick={onClick} text={buttonText}/>
  </div>;
}

export default App;