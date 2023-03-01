#include <WiFi.h>
#include "EspEasySerialCommand.h"

EspEasySerialCommand command(Serial);
//EspEasySerialCommand command;
//EspEasySerialCommand command(Serial2);

void myReset(EspEasySerialCommand::command_t command) {
  ESP.restart();
}

void wifiSet(EspEasySerialCommand::command_t command) {
  // > WIFI [SSID] [KEY]
  // command.command2 = [SSID]
  // command.command3 = [KEY]
  WiFi.begin(command.command2.c_str(), command.command3.c_str());
  Serial.print("WiFi.begin()");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (20 < i) {
      Serial.println("WiFi connection failed!");
      WiFi.disconnect();
      return;
    }

    Serial.print(".");
    delay(500);
    i++;
  }
  Serial.println("WiFi Connected.");
  Serial.printf("IP Address  : ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // preset Reset Function
  command.addCommand("RESET", EspEasySerialCommand::resetCommand);

  // anonymous function
  command.addCommand("RESET2", [](EspEasySerialCommand::command_t) {
    ESP.restart();
  });

  // normal function
  command.addCommand("RESET3", myReset);
  command.addCommand("WIFI", wifiSet); // WIFI [SSID] [KEY]
}

void loop() {
  command.task();
}
