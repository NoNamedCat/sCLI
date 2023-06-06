#include <Arduino.h>
#include "sCLI.h"

// Pin connected to the LED
const int LED_PIN = 13;

// Create an instance of the sCLI library
sCLI cli;

// Function to handle the "on" command
void turnOnCommand(char* argument) {
  digitalWrite(LED_PIN, HIGH); // Turn on the LED
  cli.print("LED turned on");
}

// Function to handle the "off" command
void turnOffCommand(char* argument) {
  digitalWrite(LED_PIN, LOW); // Turn off the LED
  cli.print("LED turned off");
}

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Add the Serial object for communication
  cli.addSerial(Serial);

  // Add the "on" and "off" commands
  cli.addCommand("on", turnOnCommand);
  cli.addCommand("off", turnOffCommand);
}

void loop() {
  // Process serial commands
  cli.loop();
}
