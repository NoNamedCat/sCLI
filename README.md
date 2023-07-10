![logo-no-background](https://github.com/NoNamedCat/sCLI/assets/39467683/66eb4f94-9409-4cea-8a28-065e23f59527)

# sCLI - Simple Command Line Interpreter Library for Arduino

![Version](https://img.shields.io/badge/version-1.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

sCLI is a small Arduino library that allows you to implement a simple command line interpreter based on user-defined functions.

## Class Reference

### sCLI

```cpp
#include <sCLI.h>
```

#### Public Member Functions

##### sCLI()

Constructs an instance of the sCLI class.

```cpp
sCLI();
```

##### void addCommand(const char *command, CommandFunction function)

Adds a command with its corresponding function to the CLI.

```cpp
void addCommand(const char *command, CommandFunction function);
```

##### void addStream(Stream &stream)

Adds a Stream object to the CLI for input/output.

```cpp
void addStream(Stream &stream);
```

##### void setPrompt(const char *prompt)

Sets the CLI prompt.

```cpp
void setPrompt(const char *prompt);
```

##### void print(const char *message)

Prints a message to all registered streams.

```cpp
void print(const char *message);
```

##### void println(const char *message)

Prints a message followed by a new line to all registered streams.

```cpp
void println(const char *message);
```

##### void printNumber(int number)

Prints a number to all registered streams.

```cpp
void printNumber(int number);
```

##### void printNumber(float number, uint8_t decimalPlaces)

Prints a floating-point number with a specified number of decimal places to all registered streams.

```cpp
void printNumber(float number, uint8_t decimalPlaces);
```

##### void executeCommand()

Executes the current command in the command buffer.

```cpp
void executeCommand();
```

##### void loop()

Main execution loop for the CLI.

```cpp
void loop();
```

