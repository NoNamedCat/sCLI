#ifndef SCLI_H
#define SCLI_H

#include <Arduino.h>
#include <Stream.h>

#define MAX_COMMAND_LENGTH 64
#define MAX_PARAMETERS 5
#define MAX_PORTS 5
#define MAX_COMMANDS 10

typedef void (*CommandFunction)(Stream& stream, const String parameters[], byte numParams);

class sCLI {
public:
  sCLI();
  void addCommand(const String& command, CommandFunction function, byte numParams);
  void addPort(Stream& stream);
  void print(const String& message);
  void loop();

private:
  Stream* ports[MAX_PORTS];
  byte numPorts;
  String inputBuffer;
  byte inputCount;
  CommandFunction commands[MAX_COMMANDS];
  String commandNames[MAX_COMMANDS];
  byte numCommands;
  String parameters[MAX_PARAMETERS];
  byte numParams;

  void processCommand();
  void clearInput();
  void printPrompt();
};

#endif

