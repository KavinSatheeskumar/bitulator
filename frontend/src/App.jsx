import "./App.css";
import React, { useState, useRef, useEffect } from "react";
import * as d3 from "d3";
import axios from "axios";
import Header from "./Header";

const MEM_WID = 16;
const MEM_HIG = 16;

const TEST_INSTRS = [
  ['ADD','SP','1','2'],
  ['ADD','MSP','SP','1'],
  ['MULT','SP','SP-1','SP-1'],
  ['ADD','MSP','SP','1'],
  ['DIV','SP','SP-1','SP-2']
]

/*
state = {
  input: string
  response: string
  instrs: string[]
  isAnimating: boolean
}
*/

function interp(inst, mem_arr) {
  console.log(inst);
}

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
    d3.select(instructionsRef.current).selectAll("table").remove();
    let CompdCode = d3
      .select(instructionsRef.current)
      .append("table")
      .append("tbody");

    let Memory = d3
      .select(instructionsRef.current)
      .append("table")
      .append("tbody");

    let mem_arr = [];

    for (let i = 0; i < MEM_WID; ++i) {
      let row = Memory.append("tr");
      for (let j = 0; j < MEM_HIG; ++j) {
        let cell = row.append("td").text("_");
        mem_arr.push(cell);
      }
    }

    let SPthing = d3.select(instructionsRef.current).append('p');

    for (let i = 0; i < instrs.length; ++i) {
      let row = CompdCode.append("tr");
      row.append("td").text(instrs[i]);
      row.transition().style("background-color", "transparent");

      if (isAnimating) {
        let command = instrs[i];
        interp(command, mem_arr);
        row
          .transition()
          .delay(1000 * i)
          .style("background-color", "#ff1e56");
      }

      row
        .transition()
        .delay(1000 * instrs.length)
        .style("background-color", "transparent");
    }
  }, [myState]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    const request = { input: myState.input };
    console.log(request);
    axios
      .post("http://bitulator.net/api", request)
      .then((res) => {
        let newInstrs = res.data.split(",").map((str) => str.split(""));
        console.log(newInstrs);
        setMyState({
          ...myState,
          response: res.data,
          instrs: TEST_INSTRS,
          isAnimating: true,
        });
      })
      .catch((error) => console.error(error));
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
      <p style={{
        color: '#ff1e56',
        fontSize: 'medium'
      }}>{myState.response}</p>
      
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
        <div
          style={{
            padding: 20,
          }}
        >
          <h3>Getting Started</h3>
          <h5>AEX</h5>
          <p>
            Short for arethmetic expression, this is any well-formed expression
            containing brackets, +, - *, /, ^, and our own operator called the
            Timbit operator ($) which comes from the opening ceremony of Hack
            The North 2021, where the conversation switched from hacking to
            Timbits. It assigns a random operand.
          </p>
          <h5>Use</h5>
          <p>
            By typing any well-formed arethmetic expression using the above
            listed operands, Bitulator will compile it into tokens, then parse
            it creating an AST, or abstract syntax tree, which then gets
            compiled into code that we use to produce an answer. You can see the
            animation made of the stack pointer moving through the stack. This
            really helps, and offers a great visual representation of how your
            simple tokens and keywords get turned into a much more complex
            thing, that we call a program, that can be used for teaching and
            learning in a much lower lever form.
          </p>
          <h5>Credits</h5>
          <p>
            Made with tender love and care by Kavin Satheeskumar, Pavlos
            Constas, Gary Zhu, and Gaurav Talreja for Hack the North 2021
          </p>
        </div>
      </div>
    </div>
  );
};

export default App;
