#ifndef SCLI_H
#define SCLI_H

#include <Arduino.h>
#include <functional>
#include <deque>

#define MAX_COMMAND_LENGTH 32
#define MAX_PARAM_COUNT 8
#define MAX_COMMAND_HISTORY 10

typedef std::function<void(const char**, uint8_t)> CommandFunction;

class sCLI {
public:
  sCLI();

  void addCommand(const char* command, CommandFunction function);
  void removeCommand(const char* command);  // New function
  void removeAllCommands();  // New function
  void addStream(Stream& stream);
  void setPrompt(const char* newPrompt);
  void setCommandNotFound(const char* message);
  void print(const char* message);
  void println(const char* message);
  void printNumber(int number);
  void printNumber(float number, uint8_t decimalPlaces);
  void printf(const char* format, ...);
  void loop();

private:
  void executeCommand();
  void processInput();
  void printPrompt();
  void tokenizeCommand(const char* command, char** tokens, uint8_t& tokenCount);
  void navigateCommandHistory(int direction);

  const char* prompt;
  CommandFunction commandFunctions[MAX_COMMAND_LENGTH];
  const char* commandNames[MAX_COMMAND_LENGTH];
  Stream* streams[MAX_COMMAND_LENGTH];
  char commandBuffer[MAX_COMMAND_LENGTH];
  uint8_t commandCount;
  uint8_t streamCount;
  uint8_t charCount;
  std::deque<String> commandHistory;
  int historyIndex;
  const char* commandNotFoundMessage;
};

#endif

