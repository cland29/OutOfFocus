#include <Stepper.h>

// Define the number of steps per revolution for the 28BYJ-48 stepper motor (this is a common value)
const int stepsPerRevolution = 32;  // For the 28BYJ-48 with ULN2003

// Define the pins connected to the ULN2003 driver
const int in1Pin = 11;  // PCB IN1
const int in2Pin = 10;  // PCB IN2
const int in3Pin = 9;   // PCB IN3
const int in4Pin = 8;   // PCB IN4

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, in1Pin, in3Pin, in2Pin, in4Pin);

void setup() {
  // Set the speed of the stepper motor in RPM
  myStepper.setSpeed(700);  // Adjust this value if needed

  // Optional: Begin serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Step forward one full revolution
  // Serial.println("Stepping forward...");
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    Serial.println("Received: " + message);
    if (isInteger(message)){
      myStepper.step(message.toInt()*32);
    }else{
      Serial.println("Please enter an integer value");
    }
  }

  //myStepper.step(stepsPerRevolution*32);
  //delay(100);  // Wait for a second

  //myStepper.step(-stepsPerRevolution*32);
  //delay(100);  // Wait for a second
}

bool isInteger(String str) {
  if (str.length() == 0) {
    return false;  // Empty string is not an integer
  }

  for (int i = 0; i < str.length(); i++) {
    Serial.println(str[i]);
    if (!isDigit(str[i]) && !(i == 0 && str[i] == 45)) {
      return false;  // If any character is not a digit, return false
    }
  }
  
  return true; // If all characters are digits, return true
}
