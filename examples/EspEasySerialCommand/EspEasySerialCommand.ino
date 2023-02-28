#include "EspEasySerialCommand.h"

EspEasySerialCommand command(Serial);
//EspEasySerialCommand command;
//EspEasySerialCommand command(Serial2);

void myReset(EspEasySerialCommand::command_t command){
  ESP.restart();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // preset Reset Function
  command.addCommand("RESET", EspEasySerialCommand::resetCommand);

  // anonymous function
  command.addCommand("RESET2", [](EspEasySerialCommand::command_t){ESP.restart();});

  // normal function
  command.addCommand("RESET3", myReset);
}

void loop() {
  command.task();
}
