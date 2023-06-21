#include "sCLI.h"
#include <math.h>

sCLI cli;

// Function to calculate the square root of a number
void calculateSqrt(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 1) {
    float number = parameters[0].toFloat();
    float result = sqrt(number);
    stream.print("Square root of ");
    stream.print(number);
    stream.print(" is: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: sqrt [number]");
  }
}

// Function to calculate the cube root of a number
void calculateCbrt(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 1) {
    float number = parameters[0].toFloat();
    float result = cbrt(number);
    stream.print("Cube root of ");
    stream.print(number);
    stream.print(" is: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: cbrt [number]");
  }
}

// Function to calculate the power of a number
void calculatePower(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float base = parameters[0].toFloat();
    float exponent = parameters[1].toFloat();
    float result = pow(base, exponent);
    stream.print(base);
    stream.print(" raised to the power of ");
    stream.print(exponent);
    stream.print(" is: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: power [base] [exponent]");
  }
}

// Function to calculate the logarithm of a number
void calculateLog(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float number = parameters[0].toFloat();
    float base = parameters[1].toFloat();
    float result = log(number) / log(base);
    stream.print("Logarithm of ");
    stream.print(number);
    stream.print(" base ");
    stream.print(base);
    stream.print(" is: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: log [number] [base]");
  }
}

// Function to perform addition
void performAddition(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float num1 = parameters[0].toFloat();
    float num2 = parameters[1].toFloat();
    float result = num1 + num2;
    stream.print("Result of addition: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: add [num1] [num2]");
  }
}

// Function to perform subtraction
void performSubtraction(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float num1 = parameters[0].toFloat();
    float num2 = parameters[1].toFloat();
    float result = num1 - num2;
    stream.print("Result of subtraction: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: subtract [num1] [num2]");
  }
}

// Function to perform multiplication
void performMultiplication(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float num1 = parameters[0].toFloat();
    float num2 = parameters[1].toFloat();
    float result = num1 * num2;
    stream.print("Result of multiplication: ");
    stream.println(result);
  } else {
    stream.println("Incorrect number of parameters. Usage: multiply [num1] [num2]");
  }
}

// Function to perform division
void performDivision(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 2) {
    float num1 = parameters[0].toFloat();
    float num2 = parameters[1].toFloat();
    if (num2 != 0) {
      float result = num1 / num2;
      stream.print("Result of division: ");
      stream.println(result);
    } else {
      stream.println("Cannot divide by zero.");
    }
  } else {
    stream.println("Incorrect number of parameters. Usage: divide [num1] [num2]");
  }
}

void setup() {
  Serial.begin(9600);
  cli.addPort(Serial);

  // Add commands to the CLI
  cli.addCommand("sqrt", calculateSqrt, 1);
  cli.addCommand("cbrt", calculateCbrt, 1);
  cli.addCommand("power", calculatePower, 2);
  cli.addCommand("log", calculateLog, 2);
  cli.addCommand("add", performAddition, 2);
  cli.addCommand("subtract", performSubtraction, 2);
  cli.addCommand("multiply", performMultiplication, 2);
  cli.addCommand("divide", performDivision, 2);
}

void loop() {
  cli.loop();
}
