#include <Arduino.h>
#include "sCLI.h"

// Pin definitions for RGB LED
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Create an instance of the sCLI library
sCLI cli;

// Function to handle the "color" command
void setColorCommand(char* argument) {
  if (strcmp(argument, "red") == 0) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  } else if (strcmp(argument, "green") == 0) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  } else if (strcmp(argument, "blue") == 0) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  } else if (strcmp(argument, "off") == 0) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  } else {
    cli.print("Invalid color. Available colors: red, green, blue, off");
  }
}

void setup() {
  // Set RGB LED pins as OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Add the Serial object for communication
  cli.addSerial(Serial);

  // Add the "color" command and assign the setColorCommand function to it
  cli.addCommand("color", setColorCommand);
}

void loop() {
  // Process serial commands
  cli.loop();
}
