import "./App.css";
import React, { useState, useRef, useEffect } from "react";
import * as d3 from "d3";
import axios from "axios";
import Header from "./Header";

const MEM_WID = 8;
const MEM_HIG = 16;

// const TEST_INSTRS = [
//   ['SET','SP','1'],
//   ['ADD','MSP','SP','1'],
//   ['SET','SP','2'],
//   ['ADD','SP','1','2'],
//   ['ADD','MSP','SP','1'],
//   ['MULT','SP','SP-1','SP-1'],
//   ['ADD','MSP','SP','1'],
//   ['DIV','SP','SP-1','SP-2']
// ]

// All operations are

// SET SP VAL
// ADD MSP SP 1
// SUB MSP SP 1
// FUNC SP-2 SP-1 SP-2

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
    instrs: [],
    isAnimating: false,
  });
  const instructionsRef = useRef();

  useEffect(() => {
    const { instrs, isAnimating } = myState;
    d3.select(instructionsRef.current).selectAll("table").remove();
    let CompdCode = d3
      .select(instructionsRef.current)
      .append("table")
      .attr('class','CompdCode')
      .append("tbody");

    let Memory = d3
      .select(instructionsRef.current)
      .append("table")
      .attr('class', 'Memory')
      .append("tbody");

    let allMemStates = [];
    let allStackStates = [];
    let SP = 0;

    if (isAnimating) {
      for (let i = 0; i < instrs.length; ++i) {
        let arr = [];
        if (allMemStates === [] || allMemStates.length === 0) {
          for (let j = 0; j < MEM_HIG; ++j){
            let sub_arr = []
            for(let k = 0; k < MEM_WID; ++k){
              sub_arr.push("");
            }
            arr.push(sub_arr);
          }
        } else {
          for (let j = 0; j < MEM_HIG; ++j){
            let sub_arr = []
              for(let k = 0; k < MEM_WID; ++k){
                sub_arr.push(allMemStates[allMemStates.length - 1][j][k]);
              }
            arr.push(sub_arr);
          }
        }

        let op = instrs[i][0];
        let loc = instrs[i][1];

        if (op === 'SET') {
          let x = SP % MEM_WID;
          let y = (SP - x)/MEM_WID;
          arr[y][x] = parseInt(instrs[i][2]);
        } else if (loc === 'MSP') {
          if (op === 'ADD') {
            ++SP;
          } else {
            --SP;
          }
        } else {
          let x2 = (SP - 2) % MEM_WID;
          let y2 = (SP - 2 - x2)/MEM_WID;

          let x1 = (SP - 1) % MEM_WID;
          let y1 = (SP - 1 - x1)/MEM_WID;
          if (op === 'ADD') {
            arr[y2][x2] = arr[y2][x2] + arr[y1][x1] 
          } else if (op === 'SUB') {
            arr[y2][x2] = arr[y2][x2] - arr[y1][x1] 
          } else if (op === 'MUL') {
            arr[y2][x2] = arr[y2][x2] * arr[y1][x1]
          } else if (op === 'DIV') {
            arr[y2][x2] = arr[y2][x2] / arr[y1][x1]
          } else if (op === 'EXP'){
            arr[y2][x2] = Math.pow(arr[y2][x2], arr[y1][x1]);
          } else {
            continue;
          }
        }

        allMemStates.push(arr);
        allStackStates.push(SP);
      }
    }

    for (let i = 0; i < MEM_HIG; ++i) {
      let row = Memory.append("tr");
      for (let j = 0; j < MEM_WID; ++j) {
        let cell = row.append("td").text("");
        if (isAnimating) {
          for (let k = 0; k < allMemStates.length; ++k) {
            cell.transition().delay(1000*k).text(allMemStates[k][i][j]);
            if (allStackStates[k] > MEM_WID * i + j) {
              cell.transition().delay(1000*k).style("background-color", "#ff8000");
            } else {
              cell.transition().delay(1000*k).style("background-color", "transparent");
            }
          }
        }
      }
    }

    for (let i = 0; i < instrs.length; ++i) {
      let row = CompdCode.append("tr");
      row.append("td").text(instrs[i]);
      row.style("background-color", "transparent");

      if (isAnimating) {
        let command = instrs[i];
        row
          .transition()
          .delay(1000 * i)
          .style("background-color", "#ff1e56");

        row
          .transition()
          .delay(1000 * (i+1))
          .style("background-color", "transparent");
      }
    }

    if (isAnimating) {
      setTimeout(() => {
        setMyState({
          ...myState,
          input: allMemStates[allMemStates.length - 1][0][0],
          isAnimating: false,
        })
      }, (allMemStates.length) * 1000);
    }
  }, [myState]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    const request = { input: myState.input };
    axios
      .post("http://bitulator.net/api", request)
      .then((res) => {
        let newInstrs = res.data.split(",").map((str) => str.split(" "));
        setMyState({
          ...myState,
          response: res.data,
          instrs: newInstrs,
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
      <div className="Instructions" ref={instructionsRef}></div>
      <div className="description">
        <div
          style={{
            padding: 20,
          }}
        >
          <h3>Getting Started</h3>
          <h4>**Please use brackets whenever using subraction, division, or timbit**</h4>
          <h5>AEX</h5>
          <p>
            Short for arethmetic expression, this is any well-formed expression
            containing brackets, +, - *, /, ^, and our own operator called the
            Timbit operator ($) which comes from the opening ceremony of Hack
            The North 2021, where the conversation switched from hacking to
            Timbits. Call each operand a random flavour of an assortement, and pick a random one.
          </p>
          <h5>Examples</h5>
          <p>
            <ul>
              <li>3+2</li>
              <li>0-(21-(12+14))</li>
              <li>8*(9/((1+2)-14))</li>
              <li>14$(14$(14$14))</li>
            </ul>
          </p>
          <h5>Use</h5>
          <p>
            By typing any well-formed arithmetic expression using the above
            listed operands, Bitulator will compile it into tokens, then parse
            it creating an AST, or abstract syntax tree, which then gets
            compiled into code that we use to produce an answer. You can see the
            animation made of the stack pointer moving through the stack. This
            really helps, and offers a great visual representation of how your
            simple tokens and keywords get turned into a much more complex
            thing, that we call a program, that can be used for teaching and
            learning in a much lower lever form.
          </p>
          <h5>Output</h5>
          <p>
              The program will return a list of instructions that operate on
            computer memory. These instructions contain a reference to two
            values, SP and MSP. SP represents the location of the next free slot
            in memory. So, whenever the program says 'SET SP [some value]', it means
            load that value into the next free location in memory. 
              There is also the value MSP. This value represnets the location where SP
            is stored. So 'ADD MSP SP 1' effectively results in SP = SP + 1. Note the
            difference between this and 'ADD SP SP 1', which would add the value SP and 1
            and then store that value in the next free location of memory.
              In our GUI, we represent the SP by highlighting all of the memory that has
            already been consumed by the program. Other than this, all of the instructions
            work exactly as one would imagine.
          </p>
          <h5>For experts</h5>
          <p>
            Our project uses React as the front end, and ExpressJS as our webserver, and 
            NodeJS as our runtime environment. Once a user clicks the Send button, the 
            data is sent to our backend, written in C++, where the AEX is validated,
            tokenized, and parsed into an Expression Tree. We then traverse the expression 
            tree using a DFS like algorithm to extract the data necessary that is posted on 
            the front end. There are also instructions written in a pseudo-Assembly manner
            that show what a computer would see if the AEX was compiled by a real computer
            language. Afterwards, we use the data to make cool animations with D3JS. 
          </p>
          <h5>Credits</h5>
          <p>
            Made with tender love and care by <a href="https://www.github.com/KavinSatheeskumar">Kavin Satheeskumar</a>, <a href='https://pconstas.mooo.com'>Pavlos
            Constas</a>, Gary Zhu, and Gaurav Talreja for Hack the North 2021
          </p>
        </div>
      </div>
    </div>
  );
};

export default App;
