const express = require('express');
const { exec } = require('child_process');
const cors = require('cors');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());

app.post('/evaluate', (req, res) => {
  const expression = req.body.expression;
  const executablePath = path.join(__dirname, 'src', 'EvaluateExpression');
  exec(`"${executablePath}" "${expression}"`, (error, stdout, stderr) => {
    if (error) {
      console.error(`exec error: ${error}`);
      return res.status(500).send(stderr);
    }
    res.send(stdout.trim());
  });
});

const PORT = 3001;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
