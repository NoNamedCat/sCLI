#include <Arduino.h>
#include <sCLI.h>

sCLI cli;

void setup() {
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("c2f", celsiusToFahrenheit);
  cli.addCommand("f2c", fahrenheitToCelsius);
}

void loop() {
  cli.loop();
}

void celsiusToFahrenheit(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: c2f <temperature>\n");
    return;
  }

  float celsius = atof(params[1]);
  float fahrenheit = (celsius * 9 / 5) + 32;

  cli.print("Fahrenheit: ");
  cli.printNumber(fahrenheit, 2);
  cli.print("\n");
}

void fahrenheitToCelsius(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: f2c <temperature>\n");
    return;
  }

  float fahrenheit = atof(params[1]);
  float celsius = (fahrenheit - 32) * 5 / 9;

  cli.print("Celsius: ");
  cli.printNumber(celsius, 2);
  cli.print("\n");
}
