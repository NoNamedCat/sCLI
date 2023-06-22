#ifndef SCLI_H
#define SCLI_H

#include <Arduino.h>
#include <Stream.h>

#define MAX_COMMAND_LENGTH 64
#define MAX_PARAM_COUNT 8

typedef void (*CommandFunction)(const char** params, uint8_t paramCount);

class sCLI {
  public:
    sCLI();
    void addCommand(const char* command, CommandFunction function);
    void addStream(Stream& stream);
    void setPrompt(const char* prompt);
    void print(const char* message);
    void println(const char* message);
    void printNumber(int number);
    void printNumber(float number, uint8_t decimalPlaces);
    void loop();

  private:
    char commandBuffer[MAX_COMMAND_LENGTH];
    const char* prompt;
    CommandFunction commandFunctions[MAX_COMMAND_LENGTH];
    const char* commandNames[MAX_COMMAND_LENGTH];
    uint8_t commandCount;
    Stream* streams[MAX_COMMAND_LENGTH];
    uint8_t streamCount;
    uint8_t charCount;

    void executeCommand();
    void processInput();
    void printPrompt();
    
    void tokenizeCommand(const char* command, char** tokens, uint8_t& tokenCount);
};

#endif
