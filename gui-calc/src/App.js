import React, { useState } from 'react';
import axios from 'axios';
import './App.css';

// Main App component for the Boolean Calculator
function App() {
  // State hooks for input and output
  const [input, setInput] = useState('');
  const [output, setOutput] = useState('');

  // Function to handle input concatenation
  const handleInput = (char) => {
    setInput(input + char);
  };

  // Function to send the expression to the backend for evaluation
  const handleCalculate = async () => {
    try {
      // Post request to the backend with the expression
      const response = await axios.post('http://localhost:3001/evaluate', { expression: input });
      const output = response.data;
      // Remove any "Invalid expression!" message from the output
      let data = output.replace("Invalid expression!", "");
      setOutput(data);
    } catch (error) {
      // Handle errors and update the output state
      console.error('Error calculating expression:', error);
      setOutput('Error evaluating expression');
    }
  };

  // JSX for rendering the Boolean Calculator UI
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

      {/* Button grid for inputting characters */}
      <div className="button-grid">
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('T')}>T</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('F')}>F</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('!')}>!</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('@')}>@</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('$')}>$</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('&')}>&</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('|')}>|</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput('(')}>(</button>
        <button style={{ backgroundColor: 'white' }} onClick={() => handleInput(')')}>)</button>
        <button style={{ backgroundColor: 'white' }} onClick={handleCalculate}>Calculate</button>
      </div>

      {/* Output display input box */}
      <input
        type="text"
        value={output}
        readOnly
        placeholder="Output will be displayed here"
        className="output-box"
      />

      {/* Footer with a company name */}
      <footer classname="footer">
        <p>RAND Corporated</p>
      </footer>
    </div>
  );
}

export default App;
