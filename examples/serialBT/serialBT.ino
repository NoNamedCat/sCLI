#include <Arduino.h>
#include <BluetoothSerial.h>
#include <sCLI.h>

BluetoothSerial SerialBT;
sCLI cli;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_BT"); // Set the Bluetooth name to "ESP32_BT"

  cli.addStream(Serial);
  cli.addStream(SerialBT);
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
