import "./App.css";
import React, { useState, useRef, useEffect } from "react";
import * as d3 from "d3";
import axios from "axios";
import Header from "./Header";

/*
state = {
  input: string
  response: string
  instrs: string[]
  isAnimating: boolean
}
*/

const App = () => {
  /*
  const [input, setInput] = useState("");
  const [response, setResponse] = useState();
  const [instrs, setInstrs] = useState(["a","b","c","d"]);
  let [isAnimating, setAnimating] = useState(false);
  */
  const [myState, setMyState] = useState({
    input: "",
    response: "",
    instrs: ["a", "b", "c", "d"],
    isAnimating: false,
  });
  const instructionsRef = useRef();

  useEffect(() => {
    const { instrs, isAnimating } = myState;
    d3.select(instructionsRef.current).select("table").remove();
    let table = d3
      .select(instructionsRef.current)
      .append("table")
      .append("tbody");
    for (let i = 0; i < instrs.length; ++i) {
      let row = table.append("tr");
      row.append("td").text(instrs[i]);
      row.append("td").text("---");
      row.transition().style("background-color", "none");
      row
        .transition()
        .delay(1000 * instrs.length)
        .style("background-color", "none");
      if (isAnimating) {
        console.log("hi");
        row
          .transition()
          .delay(1000 * i)
          .style("background-color", "red");
      }
    }
  }, [myState]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    const request = { input: myState.input };
    console.log(request);
    axios
      .post("http://bitulator.net/api", request)
      .then((res) => {
        setMyState({ ...myState, response: res.data, isAnimating: false });
      })
      .catch((error) => console.error(error));
  };

  const Animate = (e) => {
    setMyState({ ...myState, isAnimating: true });
  };

  return (
    <div className="App">
      <Header />
      <div className="input">
        <form onSubmit={handleSubmit}>
          <label>
            <input
              type="text"
              name="aex"
              value={myState.input}
              required
              placeholder="Input your AEX"
              onChange={(e) =>
                setMyState({
                  ...myState,
                  input: e.target.value,
                  isAnimating: false,
                })
              }
            />
          </label>
          <button type="submit">Send</button>
        </form>
      </div>
      <div className="response">
        <p>{myState.response}</p>
      </div>
      <button onClick={Animate}>Click to do fancy stuff</button>
      <div className="Instructions" ref={instructionsRef}>
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
      <div className="description">
        <h3>Getting Started</h3>
        <h5></h5>
      </div>
    </div>
  );
};

export default App;
