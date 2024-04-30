import React, { useState } from 'react';
import axios from 'axios';
import './App.css';

function App() {
  const [input, setInput] = useState('');
  const [output, setOutput] = useState('');

  const handleInput = (char) => {
    setInput(input + char);
  };

  const handleCalculate = async () => {
    try {
      const response = await axios.post('http://localhost:3001/evaluate', { expression: input });
      setOutput(response.data);
    } catch (error) {
      console.error('Error calculating expression:', error);
      setOutput('Error evaluating expression');
    }
  };

  return (
    <div className="app">
    <input
      type="text"
      value={input}
      onChange={(e) => setInput(e.target.value)}
      placeholder="Input goes here"
      className="input-box"
    />
    <div className="button-grid">
      <button onClick={() => handleInput('T')}>T</button>
      <button onClick={() => handleInput('F')}>F</button>
      <button onClick={() => handleInput('!')}>!</button>
      <button onClick={() => handleInput('@')}>@</button>
      <button onClick={() => handleInput('$')}>$</button>
      <button onClick={() => handleInput('&')}>&</button>
      <button onClick={() => handleInput('|')}>|</button>
      <button onClick={() => handleInput('(')}>(</button>
      <button onClick={() => handleInput(')')}>)</button>
      <button onClick={handleCalculate}>Calculate</button>
    </div>
    <input
      type="text"
      value={output}
      readOnly
      placeholder="Output shows here"
      className="output-box"
    />
  </div>
  );
}

export default App;
