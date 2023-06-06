#ifndef SCLI_H
#define SCLI_H

#include <Arduino.h>
#include <vector>

const int CLI_BUFFER_SIZE = 64;

typedef void (*CommandFunction)(char*);

class sCLI {
public:
  sCLI();
  ~sCLI();
  void addSerial(Stream& stream);
  void addCommand(const char* command, CommandFunction function);
  void loop();
  void print(const char* message);

private:
  void processLine(const char* line);
  void printPrompt(Stream* stream);

  std::vector<Stream*> _serials;
  const char* _commandStrings[CLI_BUFFER_SIZE];
  CommandFunction _commands[CLI_BUFFER_SIZE];
  char _buffer[CLI_BUFFER_SIZE];
  int _position;
  int _commandCount;
};

#endif
