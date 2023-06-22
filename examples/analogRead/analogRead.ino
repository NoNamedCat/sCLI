#include <Arduino.h>
#include <sCLI.h>

sCLI cli;
const int analogPin = A0;

void setup() {
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("readanalog", readAnalogValue);
}

void loop() {
  cli.loop();
}

void readAnalogValue(const char** params, uint8_t paramCount) {
  int value = analogRead(analogPin);
  cli.print("Analog value: ");
  cli.printNumber(value);
  cli.print("\n");
}
