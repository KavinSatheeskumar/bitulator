import "./App.css";
import React, { useState } from "react";
import axios from "axios";

const App = () => {
  const [input, setInput] = useState("");
  const [response, setResponse] = useState();

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
    </div>
  );
};

export default App;
