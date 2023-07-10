#ifndef SCLI_H
#define SCLI_H

#include <Arduino.h>
#include <Stream.h>
#include <deque>

#define MAX_COMMAND_LENGTH 64
#define MAX_PARAM_COUNT 8
#define MAX_COMMAND_HISTORY 10

typedef void (*CommandFunction)(const char** params, uint8_t paramCount);

/**
 * @brief Simple Command-Line Interface (CLI) library.
 */
class sCLI {
public:
  /**
   * @brief Constructs an instance of the sCLI class.
   */
  sCLI();

  /**
   * @brief Adds a command with its corresponding function to the CLI.
   * @param command The command string.
   * @param function The function to be executed when the command is entered.
   */
  void addCommand(const char* command, CommandFunction function);

  /**
   * @brief Adds a Stream object to the CLI for input/output.
   * @param stream The Stream object to be added.
   */
  void addStream(Stream& stream);

  /**
   * @brief Sets the CLI prompt.
   * @param prompt The prompt string.
   */
  void setPrompt(const char* prompt);

  /**
   * @brief Prints a message to all registered streams.
   * @param message The message to be printed.
   */
  void print(const char* message);

  /**
   * @brief Prints a message followed by a new line to all registered streams.
   * @param message The message to be printed.
   */
  void println(const char* message);

  /**
   * @brief Prints a number to all registered streams.
   * @param number The number to be printed.
   */
  void printNumber(int number);

  /**
   * @brief Prints a floating-point number with a specified number of decimal places to all registered streams.
   * @param number The floating-point number to be printed.
   * @param decimalPlaces The number of decimal places to include.
   */
  void printNumber(float number, uint8_t decimalPlaces);

  /**
   * @brief Executes the current command in the command buffer.
   */
  void executeCommand();

  /**
   * @brief Main execution loop for the CLI.
   */
  void loop();

private:
  char commandBuffer[MAX_COMMAND_LENGTH]; /**< Buffer to hold the current command. */
  const char* prompt; /**< Prompt string for the CLI. */
  CommandFunction commandFunctions[MAX_COMMAND_LENGTH]; /**< Array of command functions. */
  const char* commandNames[MAX_COMMAND_LENGTH]; /**< Array of command names. */
  uint8_t commandCount; /**< Number of registered commands. */
  Stream* streams[MAX_COMMAND_LENGTH]; /**< Array of registered Stream objects. */
  uint8_t streamCount; /**< Number of registered Stream objects. */
  uint8_t charCount; /**< Character count in the command buffer. */
  std::deque<String> commandHistory; /**< History of entered commands. */
  int historyIndex; /**< Index for navigating the command history. */

  /**
   * @brief Processes the input from all registered streams.
   */
  void processInput();

  /**
   * @brief Prints the CLI prompt to all registered streams.
   */
  void printPrompt();

  /**
   * @brief Tokenizes a command string into individual tokens.
   * @param command The command string to be tokenized.
   * @param tokens Array to store the resulting tokens.
   * @param tokenCount Reference to the variable to store the token count.
   */
  void tokenizeCommand(const char* command, char** tokens, uint8_t& tokenCount);

  /**
   * @brief Navigates the command history in the specified direction.
   * @param direction The direction to navigate (-1 for up, 1 for down).
   */
  void navigateCommandHistory(int direction);
};

#endif
