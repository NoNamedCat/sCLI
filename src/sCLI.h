#ifndef sCLI_h
#define sCLI_h

#include <Arduino.h>
#include <vector>

// Define the maximum length of the user input
#define CLI_BUFFER_SIZE 64

// Define a function pointer for commands
typedef void (*CommandFunction)(char*);

class sCLI {
public:
  sCLI(); // Constructor

  ~sCLI(); // Destructor

  void addSerial(Stream& stream); // Add a serial communication object

  void addCommand(const char* command, CommandFunction function); // Add a command and its corresponding function

  void loop(); // Main loop for processing commands

  void processLine(const char* line); // Process a single command line

  void print(const char* message); // Print a message to all serial communication objects

private:
  char _buffer[CLI_BUFFER_SIZE]; // Input buffer for storing user commands
  int _position; // Current position in the input buffer
  CommandFunction _commands[CLI_BUFFER_SIZE]; // Array of command functions
  const char* _commandStrings[CLI_BUFFER_SIZE]; // Array of command strings
  int _commandCount; // Number of registered commands
  std::vector<Stream*> _serials; // Vector of serial communication objects

  void printPrompt(Stream* stream); // Print the command prompt for a specific serial communication object
};

#endif
