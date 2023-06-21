#include "sCLI.h"

const int LED_PIN = 13;

// Command function to toggle the LED on or off
void toggleLed(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 1) {
    if (parameters[0] == "on") {
      digitalWrite(LED_PIN, HIGH);
      stream.println("LED turned on");
    } else if (parameters[0] == "off") {
      digitalWrite(LED_PIN, LOW);
      stream.println("LED turned off");
    } else {
      stream.println("Invalid command. Usage: led [on|off]");
    }
  } else {
    stream.println("Incorrect number of parameters. Usage: led [on|off]");
  }
}

sCLI cli;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  cli.addPort(Serial);
  cli.addCommand("led", toggleLed, 1);
}

void loop() {
  cli.loop();
}
