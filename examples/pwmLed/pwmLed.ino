#include <Arduino.h>
#include <sCLI.h>

sCLI cli;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("setbrightness", setLEDIntensity);
}

void loop() {
  cli.loop();
}

void setLEDIntensity(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: setbrightness <brightness>\n");
    return;
  }

  int brightness = atoi(params[1]);
  analogWrite(ledPin, brightness);
  cli.print("LED brightness set to: ");
  cli.printNumber(brightness);
  cli.print("\n");
}
