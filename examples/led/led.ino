#include <Arduino.h>
#include <sCLI.h>

sCLI cli;
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("onLED", turnOnLED);
  cli.addCommand("offLED", turnOffLED);
}

void loop() {
  cli.loop();
}

void turnOnLED(const char** params, uint8_t paramCount) {
  digitalWrite(ledPin, HIGH);
  cli.print("LED turned on\n");
}

void turnOffLED(const char** params, uint8_t paramCount) {
  digitalWrite(ledPin, LOW);
  cli.print("LED turned off\n");
}
