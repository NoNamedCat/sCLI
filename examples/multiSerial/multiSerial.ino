#include <Arduino.h>
#include <sCLI.h>

sCLI cli;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Second serial port

  cli.addStream(Serial);
  cli.addStream(Serial1);
  cli.setPrompt("sCLI> ");

  cli.addCommand("hello", sayHello);
}

void loop() {
  cli.loop();
}

void sayHello(const char** params, uint8_t paramCount) {
  cli.print("Hello from sCLI!");
  cli.print("\n");
}
