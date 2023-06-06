#include "sCLI.h"

sCLI::sCLI() : _position(0), _commandCount(0) {
  memset(_buffer, 0, sizeof(_buffer)); // Clear the input buffer
}

sCLI::~sCLI() {
  _serials.clear(); // Clear the vector of serial communication objects
}

void sCLI::addSerial(Stream& stream) {
  _serials.push_back(&stream); // Add a serial communication object to the vector
}

void sCLI::addCommand(const char* command, CommandFunction function) {
  if (_commandCount < CLI_BUFFER_SIZE) {
    _commandStrings[_commandCount] = command; // Add the command string to the array
    _commands[_commandCount] = function; // Add the command function to the array
    _commandCount++; // Increment the number of registered commands
  }
}

void sCLI::loop() {
  for (auto& stream : _serials) {
    while (stream->available()) {
      char c = stream->read(); // Read a character from the serial input

      // Check for end of line character
      if (c == '\r' || c == '\n') {
        stream->println(); // Print a new line
        processLine(stream, _buffer); // Process the command line
        printPrompt(stream); // Print the command prompt
      }
      // Check for backspace or delete character
      else if (c == '\b' || c == 0x7f) {
        if (_position > 0) {
          _position--; // Decrement the current position in the input buffer
          stream->print('\b'); // Move the cursor back
          stream->print(' '); // Clear the character
          stream->print('\b'); // Move the cursor back again
        }
      }
      // Store the character in the input buffer
      else if (_position < CLI_BUFFER_SIZE - 1) {
        _buffer[_position] = c;
        _position++;
        stream->write(c); // Echo the character back to the serial output
      }
    }
  }
}

void sCLI::processLine(const char* line) {
  _buffer[_position] = 0; // Null-terminate the input buffer
  for (int i = 0; i < _commandCount; i++) {
    if (strcmp(_buffer, _commandStrings[i]) == 0) {
      _commands[i](""); // Call the command function with an empty argument
      return;
    }
    if (strncmp(_buffer, _commandStrings[i], strlen(_commandStrings[i])) == 0) {
      _commands[i](_buffer + strlen(_commandStrings[i]) + 1); // Call the command function with the argument after the command string
      return;
    }
  }
  stream->print("Unknown command: "); // Print an error message for unknown commands
  stream->println(_buffer);
}

void sCLI::printPrompt(Stream* stream) {
  stream->print("> "); // Print the command prompt
  _position = 0; // Reset the current position in the input buffer
  memset(_buffer, 0, sizeof(_buffer)); // Clear the input buffer
}

void sCLI::print(const char* message) {
  for (auto& stream : _serials) {
    stream->print(message); // Print the message to all serial communication objects
  }
}
