#include "sCLI.h"

const int SENSOR_PIN = A0;

// Command function to read the sensor value
void readSensor(Stream& stream, const String parameters[], byte numParams) {
  if (numParams == 0) {
    int sensorValue = analogRead(SENSOR_PIN);
    stream.print("Sensor value: ");
    stream.println(sensorValue);
  } else {
    stream.println("This command does not require parameters.");
  }
}

sCLI cli;

void setup() {
  Serial.begin(9600);
  cli.addPort(Serial);
  cli.addCommand("sensor", readSensor, 0);
}

void loop() {
  cli.loop();
}
