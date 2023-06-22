#include <Arduino.h>
#include <sCLI.h>

sCLI cli;

void setup() {
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("echo", echoCommand);
}

void loop() {
  cli.loop();
}

void echoCommand(const char** params, uint8_t paramCount) {
  if (paramCount < 2) {
    cli.print("Usage: echo <text>\n");
    return;
  }

  for (uint8_t i = 1; i < paramCount; i++) {
    cli.print(params[i]);
    cli.print(" ");
  }

  cli.print("\n");
}
