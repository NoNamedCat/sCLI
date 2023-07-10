![logo-no-background](https://github.com/NoNamedCat/sCLI/assets/39467683/66eb4f94-9409-4cea-8a28-065e23f59527)

Small arduino library to implement a simple command line interpreter based on the user defined functions.



sCLI Class Reference

Simple Command-Line Interface (CLI) library.

#include <sCLI.h>

Public Member Functions

sCLI ()

Constructs an instance of the sCLI class. 

void addCommand (const char *command, CommandFunction function)
Adds a command with its corresponding function to the CLI. 

void addStream (Stream &stream)
Adds a Stream object to the CLI for input/output. 

void setPrompt (const char *prompt)
Sets the CLI prompt. 

void print (const char *message)
Prints a message to all registered streams. 

void println (const char *message)
Prints a message followed by a new line to all registered streams. 

void printNumber (int number)
Prints a number to all registered streams. 

void printNumber (float number, uint8_t decimalPlaces)
Prints a floating-point number with a specified number of decimal places to all registered streams. 

void executeCommand ()
Executes the current command in the command buffer. 

void loop ()
Main execution loop for the CLI. 

