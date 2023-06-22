#include "sCLI.h"

sCLI::sCLI() {
  prompt = "> ";
  commandCount = 0;
  streamCount = 0;
  charCount = 0;
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

void sCLI::loop() {
    processInput();
}

void sCLI::executeCommand() {
  size_t commandLength = strlen(commandBuffer);

  // Verificar si el comando está vacío o consiste solo en espacios en blanco
  bool isWhitespaceOnly = true;
  for (size_t i = 0; i < commandLength; i++) {
    if (!isspace(commandBuffer[i])) {
      isWhitespaceOnly = false;
      break;
    }
  }

  if (commandLength == 0 || isWhitespaceOnly) {
    // El comando está vacío o consiste solo en espacios en blanco, ignorarlo
    memset(commandBuffer, 0, sizeof(commandBuffer));
    charCount = 0;
    return;
  }

  char* tokens[MAX_PARAM_COUNT];
  uint8_t tokenCount = 0;

  

  tokenizeCommand(commandBuffer, tokens, tokenCount);

  for (uint8_t i = 0; i < commandCount; i++) {
    if (strcmp(tokens[0], commandNames[i]) == 0) {
      commandFunctions[i]((const char**)tokens, tokenCount);
      break;
    }
  }

  // Clear command buffer
  memset(commandBuffer, 0, sizeof(commandBuffer));
  charCount = 0;
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
      streams[i]->flush();   // Asegurarse de que los datos se envíen correctamente
    }
  }
}

void sCLI::println(const char* message) {
  for (uint8_t i = 0; i < streamCount; i++) {
    if (streams[i] != nullptr) {
      streams[i]->print(message);
      streams[i]->println(); // Agregar una nueva línea al final del mensaje
      streams[i]->flush();   // Asegurarse de que los datos se envíen correctamente
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
}
