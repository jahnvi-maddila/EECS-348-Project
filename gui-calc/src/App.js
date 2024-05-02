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
      const output=response.data;
      let data = output.replace("Invalid expression!","");
      setOutput(data);
    } catch (error) {
      console.error('Error calculating expression:', error);
      setOutput('Error evaluating expression');
    }
  };


  return (
    <div className="app">
    <header className="app-header">
        Boolean Calculator
    </header>
    <a className="about" href="/about.html">About</a>
    <div className='inputwrapper'>
      <input
        type="text"
        value={input}
        onChange={(e) => setInput(e.target.value)}
        placeholder="Input your expression here"
        className="input-box"
      />
      {input && <button className='buttonininput' onClick={() => setInput('')}>Clear</button>}
    </div>
    

    <div className="button-grid">
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('T')}>T</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('F')}>F</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('!')}>!</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('@')}>@</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('$')}>$</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('&')}>&</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('|')}>|</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput('(')}>(</button>
      <button style={{backgroundColor: 'white'}} onClick={() => handleInput(')')}>)</button>
      <button style={{backgroundColor: 'white'}} onClick={handleCalculate}>Calculate</button>
    </div>
  
    <input
      type="text"
      value={output}
      readOnly
      placeholder="Output will be displayed here"
      className="output-box"
    />
    <footer classname = "footer">
      <p>RAND Corporated</p>
    </footer>
  </div>
  
  );
}

export default App;
