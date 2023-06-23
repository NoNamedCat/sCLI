#include <Arduino.h>
#include <sCLI.h>
#include <math.h>

sCLI cli;

void setup() {
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");

  // Add command functions
  cli.addCommand("add", add);
  cli.addCommand("subtract", subtract);
  cli.addCommand("multiply", multiply);
  cli.addCommand("divide", divide);
  cli.addCommand("sqrt", squareRoot);
  cli.addCommand("power", power);
  cli.addCommand("log", logarithm); 
}

void loop() {
  // Start sCLI
  cli.loop();
}

// Command Functions

void add(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: add <num1> <num2>\n");
    return;
  }

  float num1 = atof(params[1]);
  float num2 = atof(params[2]);
  float result = num1 + num2;

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void subtract(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: subtract <num1> <num2>\n");
    return;
  }

  float num1 = atof(params[1]);
  float num2 = atof(params[2]);
  float result = num1 - num2;

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void multiply(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: multiply <num1> <num2>\n");
    return;
  }

  float num1 = atof(params[1]);
  float num2 = atof(params[2]);
  float result = num1 * num2;

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void divide(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: divide <num1> <num2>\n");
    return;
  }

  float num1 = atof(params[1]);
  float num2 = atof(params[2]);

  if (num2 == 0) {
    cli.print("Error: Division by zero\n");
    return;
  }

  float result = num1 / num2;

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void squareRoot(const char** params, uint8_t paramCount) {
  if (paramCount != 1) {
    cli.print("Usage: sqrt <num>\n");
    return;
  }

  float num = atof(params[1]);

  if (num < 0) {
    cli.print("Error: Invalid input\n");
    return;
  }

  float result = sqrt(num);

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void power(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: power <base> <exponent>\n");
    return;
  }

  float base = atof(params[1]);
  float exponent = atof(params[2]);
  float result = pow(base, exponent);

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

void logarithm(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: log <base> <number>\n");
    return;
  }

  float base = atof(params[1]);
  float number = atof(params[2]);

  if (base <= 0 || number <= 0) {
    cli.print("Error: Invalid input\n");
    return;
  }

  float result = log(number) / log(base);

  cli.print("Result: ");
  cli.printNumber(result);
  cli.print("\n");
}

