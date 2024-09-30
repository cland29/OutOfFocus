#include <Stepper.h>

// Define the number of steps per revolution for the 28BYJ-48 stepper motor (this is a common value)
const int stepsPerRevolution = 2048;  // For the 28BYJ-48 with ULN2003

// Define the pins connected to the ULN2003 driver
const int in1Pin = 11;  // PCB IN1
const int in2Pin = 10;  // PCB IN2
const int in3Pin = 9;   // PCB IN3
const int in4Pin = 8;   // PCB IN4

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  // Set the speed of the stepper motor in RPM
  myStepper.setSpeed(10);  // Adjust this value if needed

  // Optional: Begin serial communication for debugging
  Serial.begin(9600);
  Serial.println("Stepper Motor Test");
}

void loop() {
  // Step forward one full revolution
  Serial.println("Stepping forward...");
  myStepper.step(stepsPerRevolution);
  delay(1000);  // Wait for a second

  // Step backward one full revolution
  Serial.println("Stepping backward...");
  myStepper.step(-stepsPerRevolution);
  delay(1000);  // Wait for a second
}
