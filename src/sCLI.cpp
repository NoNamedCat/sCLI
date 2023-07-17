#include "sCLI.h"

sCLI::sCLI() {
  prompt = "> ";
  commandCount = 0;
  streamCount = 0;
  charCount = 0;
  historyIndex = -1;
  commandNotFoundMessage = nullptr;  
}

void sCLI::addCommand(const char* command, CommandFunction function) {
  if (commandCount < MAX_COMMAND_LENGTH) {
    commandNames[commandCount] = command;
    commandFunctions[commandCount] = function;
    commandCount++;
  }
}

void sCLI::addStream(Stream& stream) {
  if (streamCount < MAX_COMMAND_LENGTH) {
    streams[streamCount] = &stream;
    streamCount++;
  }
}

void sCLI::setPrompt(const char* newPrompt) {
  prompt = newPrompt;
  printPrompt();
}

void sCLI::setCommandNotFound(const char* message) {
  commandNotFoundMessage = message;
}

void sCLI::loop() {
  processInput();
}

void sCLI::executeCommand() {
  size_t commandLength = strlen(commandBuffer);

  // Check if the command is empty or consists only of whitespace
  bool isWhitespaceOnly = true;
  for (size_t i = 0; i < commandLength; i++) {
    if (!isspace(commandBuffer[i])) {
      isWhitespaceOnly = false;
      break;
    }
  }

  if (commandLength == 0 || isWhitespaceOnly) {
    // The command is empty or consists only of whitespace, ignore it
    memset(commandBuffer, 0, sizeof(commandBuffer));
    charCount = 0;
    return;
  }

  char* tokens[MAX_PARAM_COUNT];
  uint8_t tokenCount = 0;

  tokenizeCommand(commandBuffer, tokens, tokenCount);

  bool commandFound = false;  // Track if the command is found

  for (uint8_t i = 0; i < commandCount; i++) {
    if (strcmp(tokens[0], commandNames[i]) == 0) {
      commandFunctions[i]((const char**)tokens, tokenCount);
      commandFound = true;  // Set commandFound to true
      break;
    }
  }

  if (!commandFound && commandNotFoundMessage != nullptr) {
    // Command not found, print the custom message
    println(commandNotFoundMessage);
  }

  // Check if the command already exists in the history
  bool commandExists = false;
  for (const String& historyCommand : commandHistory) {
    if (historyCommand.equals(commandBuffer)) {
      commandExists = true;
      break;
    }
  }

  if (!commandExists) {
    // Add the current command to the history
    commandHistory.push_front(commandBuffer);

    // Clear the history if it exceeds a maximum limit
    if (commandHistory.size() > MAX_COMMAND_HISTORY) {
      commandHistory.pop_back();
    }
  }

  // Clear the command buffer and reset the character count
  memset(commandBuffer, 0, sizeof(commandBuffer));
  charCount = 0;

  // Reset the history index to -1
  historyIndex = -1;
}

void sCLI::processInput() {
  for (uint8_t i = 0; i < streamCount; i++) {
    Stream* stream = streams[i];
    while (stream->available()) {
      char input = stream->read();

      if (charCount < MAX_COMMAND_LENGTH) {
        if (input == '\r' || input == '\n') {
          if (charCount > 0) {
            println("");
            executeCommand();
            printPrompt();
          }
        } else if (input == '\b' || input == 127) {  // Backspace or Delete key
          if (charCount > 0) {
            charCount--;
            for (uint8_t j = 0; j < streamCount; j++) {
              if (streams[j] != nullptr) {
                streams[j]->write("\b \b");
              }
            }
          }
        } else if (input == '\e') {  // Escape character
          input = stream->read();
          if (input == '[') {
            input = stream->read();
            if (input == 'B') {  // Down arrow (previously Up arrow)
              navigateCommandHistory(1);  // Changed direction
            } else if (input == 'A') {  // Up arrow (previously Down arrow)
              navigateCommandHistory(-1);  // Changed direction
            }
          }
        } else {
          commandBuffer[charCount] = input;
          charCount++;
          for (uint8_t j = 0; j < streamCount; j++) {
            if (streams[j] != nullptr) {
              streams[j]->write(input);
            }
          }
        }
      }
    }
  }
}

void sCLI::printPrompt() {
  print(prompt);
}

void sCLI::print(const char* message) {
  for (uint8_t i = 0; i < streamCount; i++) {
    if (streams[i] != nullptr) {
      streams[i]->print(message);
      streams[i]->flush();   // Make sure the data is sent correctly
    }
  }
}

void sCLI::println(const char* message) {
  for (uint8_t i = 0; i < streamCount; i++) {
    if (streams[i] != nullptr) {
      streams[i]->print(message);
      streams[i]->println(); // Add a new line at the end of the message
      streams[i]->flush();   // Make sure the data is sent correctly
    }
  }
}

void sCLI::printNumber(int number) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%d", number);
  print(buffer);
}

void sCLI::printNumber(float number, uint8_t decimalPlaces) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.*f", decimalPlaces, number);
  print(buffer);
}

void sCLI::printf(const char* format, ...) {
  char buffer[MAX_COMMAND_LENGTH];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  print(buffer);
}

void sCLI::tokenizeCommand(const char* command, char** tokens, uint8_t& tokenCount) {
  char* token;
  char* commandCopy = strdup(command);

  token = strtok(commandCopy, " ");
  while (token != nullptr) {
    tokens[tokenCount] = token;
    tokenCount++;
    token = strtok(nullptr, " ");
  }

  free(commandCopy);
  tokenCount--;  // Adjust the count to exclude the main command
}

void sCLI::navigateCommandHistory(int direction) {
  if (commandHistory.empty()) {
    return;
  }

  // Update the history index
  historyIndex -= direction;  // Inverted direction

  // Make sure the history index is within valid bounds
  if (historyIndex < -1) {  // Adjusted condition
    historyIndex = -1;  // Changed value
  } else if (historyIndex >= static_cast<int>(commandHistory.size() - 1)) {  // Adjusted condition
    historyIndex = commandHistory.size() - 1;  // Changed value
  }

  // Clear the current line
  for (uint8_t i = 0; i < streamCount; i++) {
    if (streams[i] != nullptr) {
      streams[i]->write('\r');
      for (uint8_t j = 0; j < MAX_COMMAND_LENGTH; j++) {
        streams[i]->write(' ');
      }
      streams[i]->write('\r');
    }
  }

  // Get the command from the history based on the index
  String previousCommand;
  if (historyIndex >= 0) {
    previousCommand = commandHistory[historyIndex];
  }

  // Update the command buffer and character count
  strncpy(commandBuffer, previousCommand.c_str(), MAX_COMMAND_LENGTH - 1);
  commandBuffer[MAX_COMMAND_LENGTH - 1] = '\0';
  charCount = previousCommand.length();

  // Show the command in the CLI
  for (uint8_t i = 0; i < streamCount; i++) {
    if (streams[i] != nullptr) {
      streams[i]->print(prompt);
      streams[i]->print(previousCommand);
    }
  }
}

