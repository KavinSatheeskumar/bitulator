import "./App.css";
import React, { useState, useRef, useEffect } from "react";
import * as d3 from 'd3';
import axios from "axios";
import Header from './Header';

const App = () => {
  const [input, setInput] = useState("");
  const [response, setResponse] = useState();
  const [instrs, setInstrs] = useState(["a","b","c","d"]);
  const [isAnimating, setAnimating] = useState(false);
  const instructionsRef = useRef()

  useEffect(() => {
    d3.select(instructionsRef.current).select('table').remove();
    let table = d3.select(instructionsRef.current)
              .append('table').append('tbody');
    let rows = [];
    for (let i = 0; i < instrs.length; ++i) {
      let row = table.append('tr');
      row.append('td').text(instrs[i]);
      row.append('td').text('---');
      rows.push(row);
    }
    if (isAnimating) {
      for (let i = 0; i < rows.length; ++i) {
        //rows[i].transition().delay(1000*i).styles('background-color','red');
      }
    }
    setAnimating(false);
  }, [isAnimating, instrs])

  const handleSubmit = async (e) => {
    e.preventDefault();
    const request = { input };
    console.log(request)
    axios
      .post("http://localhost:80/api", request)
      .then((res) => {
        setResponse(res.data);
      })
      .catch((error) => console.error(error));
  };

  const Animate = (e) => {
    setAnimating(true);
  }

  return (
    <div className="App">
      <Header />
      <div className="input">
        <form onSubmit={handleSubmit}>
          <label>
            <input
              type="text"
              name="aex"
              value={input}
              required
              placeholder="Input your AEX"
              onChange={(e) => setInput(e.target.value)}
            />
          </label>
          <button type="submit">Send</button>
        </form>
      </div>
      <div className="response"><p>{response}</p></div>
      
      <button onClick={Animate}>Click to do fancy stuff</button>
      <div 
        className="Instructions"
        ref={instructionsRef}
      >
      {/*
        <table 
          id="Code"
          ref={instructionsRef}
        >
          <tbody>
            {instrs.map((str, i) => (
                <tr>
                  <td>{str}</td>
                  <td>{i === currentInstr ? "===" : "---"}</td>
                </tr>
              ))}
          </tbody>
        </table>
      */}
      </div>
    </div>
  );
};

export default App;
