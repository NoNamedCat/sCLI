#include <Arduino.h>
#include "sCLI.h"

// Create an instance of the sCLI library
sCLI cli;

// Function to handle addition
void additionCommand(char* argument) {
  // Parse the operands from the argument
  char* operand1 = strtok(argument, " ");
  char* operand2 = strtok(NULL, " ");

  // Check if both operands are provided
  if (operand1 && operand2) {
    // Convert operands to floats
    float num1 = atof(operand1);
    float num2 = atof(operand2);

    // Perform addition and print the result
    float result = num1 + num2;
    char message[20];
    snprintf(message, sizeof(message), "Result: %.2f", result);
    cli.print(message);
  } else {
    cli.print("Invalid command format. Usage: addition <operand1> <operand2>");
  }
}

// Function to handle subtraction
void subtractionCommand(char* argument) {
  // Parse the operands from the argument
  char* operand1 = strtok(argument, " ");
  char* operand2 = strtok(NULL, " ");

  // Check if both operands are provided
  if (operand1 && operand2) {
    // Convert operands to floats
    float num1 = atof(operand1);
    float num2 = atof(operand2);

    // Perform subtraction and print the result
    float result = num1 - num2;
    char message[20];
    snprintf(message, sizeof(message), "Result: %.2f", result);
    cli.print(message);
  } else {
    cli.print("Invalid command format. Usage: subtraction <operand1> <operand2>");
  }
}

// Function to handle multiplication
void multiplicationCommand(char* argument) {
  // Parse the operands from the argument
  char* operand1 = strtok(argument, " ");
  char* operand2 = strtok(NULL, " ");

  // Check if both operands are provided
  if (operand1 && operand2) {
    // Convert operands to floats
    float num1 = atof(operand1);
    float num2 = atof(operand2);

    // Perform multiplication and print the result
    float result = num1 * num2;
    char message[20];
    snprintf(message, sizeof(message), "Result: %.2f", result);
    cli.print(message);
  } else {
    cli.print("Invalid command format. Usage: multiplication <operand1> <operand2>");
  }
}

// Function to handle division
void divisionCommand(char* argument) {
  // Parse the operands from the argument
  char* operand1 = strtok(argument, " ");
  char* operand2 = strtok(NULL, " ");

  // Check if both operands are provided
  if (operand1 && operand2) {
    // Convert operands to floats
    float num1 = atof(operand1);
    float num2 = atof(operand2);

    // Check for division by zero
    if (num2 != 0) {
      // Perform division and print the result
      float result = num1 / num2;
      char message[20];
      snprintf(message, sizeof(message), "Result: %.2f", result);
      cli.print(message);
    } else {
      cli.print("Error: Division by zero!");
    }
  } else {
    cli.print("Invalid command format. Usage: division <operand1> <operand2>");
  }
}

void setup() {
  // Add the Serial object for communication
  cli.addSerial(Serial);

  // Add the commands for each arithmetic operation
  cli.addCommand("addition", additionCommand);
  cli.addCommand("subtraction", subtractionCommand);
  cli.addCommand("multiplication", multiplicationCommand);
  cli.addCommand("division", divisionCommand);
}

void loop() {
  // Process serial commands
  cli.loop();
}
