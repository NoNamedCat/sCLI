#include <Arduino.h>
#include <SoftwareSerial.h>
#include <sCLI.h>

SoftwareSerial mySerial(10, 11); // RX, TX pins for SoftwareSerial
sCLI cli;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  cli.addStream(Serial);
  cli.addStream(mySerial);
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
