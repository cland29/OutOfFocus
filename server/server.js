const express = require('express');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const app = express();
const port = 3000;

// Replace '/dev/ttyUSB0' with your Arduino's serial port
const serialPort = new SerialPort({
  path: '/dev/ttyUSB0', // Update this path for your system
  baudRate: 9600,
});

const parser = serialPort.pipe(new Readline({ delimiter: '\n' }));

// Middleware to parse JSON requests
app.use(express.json());

// Handle incoming messages from the Arduino
parser.on('data', (data) => {
  console.log(`Received from Arduino: ${data}`);
});

// Endpoint to send data to Arduino
app.post('/send', (req, res) => {
  const message = req.body.message;

  if (message) {
    serialPort.write(`${message}\n`, (err) => {
      if (err) {
        return res.status(500).send('Error on write: ' + err.message);
      }
      console.log(`Sent to Arduino: ${message}`);
      res.status(200).send('Message sent to Arduino');
    });
  } else {
    res.status(400).send('No message provided');
  }
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});