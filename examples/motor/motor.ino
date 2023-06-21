#include "sCLI.h"

const int MOTOR_PIN = 9;

// Command function to set the motor speed
void setMotorSpeed(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 1) {
    int speed = parameters[0].toInt();
    if (speed >= 0 && speed <= 255) {
      analogWrite(MOTOR_PIN, speed);
      stream.print("Motor speed set: ");
      stream.println(speed);
    } else {
      stream.println("Invalid speed value. Range: 0-255");
    }
  } else {
    stream.println("Incorrect number of parameters. Usage: motor [speed]");
  }
}

sCLI cli;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  cli.addPort(Serial);
  cli.addCommand("motor", setMotorSpeed, 1);
}

void loop() {
  cli.loop();
}
