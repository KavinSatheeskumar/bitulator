import "./App.css";
import React, { useState, useRef, useEffect } from "react";
import * as d3 from 'd3';
import axios from "axios";

const App = () => {
  const [input, setInput] = useState("");
  const [response, setResponse] = useState();
  const [instrs, setInstrs] = useState(["a","b","c","d"]);
  const [isAnimating, setAnimating] = useState(false);
  const [currentInstr, setCurrentInstr] = useState(-1);
  const instructionsRef = useRef()

  useEffect(() => {
    if (isAnimating) {
      d3.select("#Code")
        .transition()
        .delay(1000)
        .style("background-color", "red");
    }
    setAnimating(false);
  })

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
      <p>{response}</p>
      <button onClick={Animate}>Click to do fancy stuff</button>
      <div className="Instructions">
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
      </div>
    </div>
  );
};

export default App;
