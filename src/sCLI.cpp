#include "sCLI.h"



sCLI::sCLI() {
  numPorts = 0;
  inputCount = 0;
  numCommands = 0;
  numParams = 0;
}

void sCLI::addCommand(const String& command, CommandFunction function, byte numParams) {
  if (numCommands < MAX_COMMANDS) {
    commandNames[numCommands] = command;
    commands[numCommands] = function;
    numCommands++;
  }
}

void sCLI::addPort(Stream& stream) {
  if (numPorts < MAX_PORTS) {
    ports[numPorts] = &stream;
    numPorts++;
  }
}

void sCLI::print(const String& message) {
  for (byte i = 0; i < numPorts; i++) {
    ports[i]->print(message);
  }
}

void sCLI::loop() {
  while (ports[0]->available()) {
    char c = ports[0]->read();
    if (c == '\r' || c == '\n') {
      if (inputCount > 0) {
        processCommand();
        clearInput();
      }
      printPrompt();
    } else if (c == '\b') {
      if (inputCount > 0) {
        inputBuffer.remove(inputCount - 1);
        inputCount--;
        print("\b \b");
      }
    } else if (inputCount < MAX_COMMAND_LENGTH) {
      inputBuffer += c;
      inputCount++;
      print(String(c));
    }
  }
}

void sCLI::processCommand() {
  String command;
  byte paramStart = 0;
  byte paramEnd = inputBuffer.indexOf(' ');
  if (paramEnd == -1) {
    command = inputBuffer;
  } else {
    command = inputBuffer.substring(0, paramEnd);
    paramStart = paramEnd + 1;
  }

  for (byte i = 0; i < numCommands; i++) {
    if (command.equals(commandNames[i])) {
      numParams = 0;
      byte paramIndex = 0;
      while (paramStart < inputCount && numParams < MAX_PARAMETERS) {
        paramEnd = inputBuffer.indexOf(' ', paramStart);
        if (paramEnd == -1) {
          paramEnd = inputCount;
        }
        parameters[paramIndex] = inputBuffer.substring(paramStart, paramEnd);
        paramIndex++;
        paramStart = paramEnd + 1;
        numParams++;
      }
      for (byte j = 0; j < numPorts; j++) {
        commands[i](*ports[j], parameters, numParams);
      }
      clearInput();
      return;
    }
  }
  print("Command not found: ");
  print(command);
  print("\n");
  clearInput();
}
