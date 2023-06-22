#include <Arduino.h>
#include <sCLI.h>
#include <Servo.h>

sCLI cli;
Servo myservo;
const int servoPin = 9;

void setup() {
  Serial.begin(9600);
  cli.addStream(Serial);
  cli.setPrompt("sCLI> ");
  cli.addCommand("servo", controlServo);
  myservo.attach(servoPin);
}

void loop() {
  cli.loop();
}

void controlServo(const char** params, uint8_t paramCount) {
  if (paramCount != 2) {
    cli.print("Usage: servo <angle>\n");
    return;
  }

  int angle = atoi(params[1]);
  myservo.write(angle);
  cli.print("Servo angle set to: ");
  cli.printNumber(angle);
  cli.print("\n");
}
