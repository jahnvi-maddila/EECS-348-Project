const express = require('express');
const { exec } = require('child_process');
const cors = require('cors');
const path = require('path');

// Create a new Express application instance
const app = express();

// Middleware to enable CORS (Cross-Origin Resource Sharing)
app.use(cors());

// Middleware to parse JSON bodies
app.use(express.json());

// POST endpoint to evaluate expressions using an external executable
app.post('/evaluate', (req, res) => {
  // Extract expression from request body
  const expression = req.body.expression;

  // Determine the path to the executable that evaluates the expression
  const executablePath = path.join(__dirname, 'src', 'EvaluateExpression');

  // Execute the external program with the expression as an argument
  exec(`"${executablePath}" "${expression}"`, (error, stdout, stderr) => {
    if (error) {
      // Log any execution errors
      console.error(`exec error: ${error}`);
      // Send the output from the executable, typically error messages or results
      return res.send(stdout.trim());
    }
    // Send the successful output back to the client
    res.send(stdout.trim());
  });
});

// Define the port number on which the server will listen
const PORT = 3001;
app.listen(PORT, () => {
  // Confirmation that the server is running
  console.log(`Server running on http://localhost:${PORT}`);
});
