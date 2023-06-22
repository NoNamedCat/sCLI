#include <Arduino.h>
#include <Serial.h>
#include <sCLI.h>
#include <math.h>

sCLI cli;

void setup() {
  Serial.begin(9600);
  
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  
  cli.addCommand("sum", sumCommand);
  cli.addCommand("multiply", multiplyCommand);
  cli.addCommand("power", powerCommand);
  cli.addCommand("log", logCommand);
  cli.addCommand("root", rootCommand);
}

void loop() {
  cli.loop();
}

void sumCommand(const char** params, uint8_t paramCount) {
  if (paramCount < 2) {
    cli.print("Insufficient number of parameters. Usage: sum <num1> <num2>");
    cli.print("\n");
    return;
  }
  
  int sum = 0;
  for (uint8_t i = 0; i < paramCount; i++) {
    sum += atoi(params[i]);
  }
  
  cli.print("Sum: ");
  cli.printNumber(sum);
  cli.print("\n");
}

void multiplyCommand(const char** params, uint8_t paramCount) {
  if (paramCount < 2) {
    cli.print("Insufficient number of parameters. Usage: multiply <num1> <num2>");
    cli.print("\n");
    return;
  }
  
  int product = 1;
  for (uint8_t i = 0; i < paramCount; i++) {
    product *= atoi(params[i]);
  }
  
  cli.print("Product: ");
  cli.printNumber(product);
  cli.print("\n");
}

void powerCommand(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Invalid number of parameters. Usage: power <base> <exponent>");
    cli.print("\n");
    return;
  }
  
  float base = atof(params[0]);
  float exponent = atof(params[1]);
  
  float result = pow(base, exponent);
  
  cli.print("Result: ");
  cli.printNumber(result, 2);
  cli.print("\n");
}

void logCommand(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Invalid number of parameters. Usage: log <number> <base>");
    cli.print("\n");
    return;
  }
  
  float number = atof(params[0]);
  float base = atof(params[1]);
  
  float result = log(number) / log(base);
  
  cli.print("Result: ");
  cli.printNumber(result, 2);
  cli.print("\n");
}

void rootCommand(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Invalid number of parameters. Usage: root <number> <degree>");
    cli.print("\n");
    return;
  }
  
  float number = atof(params[0]);
  float degree = atof(params[1]);
  
  if (degree == 0) {
    cli.print("Degree cannot be zero");
    cli.print("\n");
    return;
  }
  
  float result = pow(number, 1 / degree);
  
  cli.print("Result: ");
  cli.printNumber(result, 2);
  cli.print("\n");
}
