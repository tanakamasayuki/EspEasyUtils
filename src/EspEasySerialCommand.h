#ifndef __EspEasySerialCommand_H__
#define __EspEasySerialCommand_H__

class EspEasySerialCommand {
public:
  typedef struct {
    String command2;
    String command3;
    String command4;
  } command_t;

  Stream *_serial;
  static const int8_t maxCommand = 32;
  void (*pFunctions[maxCommand])(command_t);
  String commandList[maxCommand];
  uint8_t commandCount;

  EspEasySerialCommand(Stream &serial = Serial) {
    _serial = &serial;
    commandCount = 0;
  };

  void addCommand(String command, void (*function)(command_t)) {
    if (maxCommand <= commandCount) {
      return;
    }
    commandList[commandCount] = command;
    pFunctions[commandCount] = function;
    commandCount++;
  };

  void task(void) {
    while (_serial->available()) {
      char input[256];
      command_t cmd = {};
      String command = _serial->readStringUntil('\n');
      command.trim();
      strncpy(input, command.c_str(), sizeof(input) - 1);
      char *command0 = strtok(input, " ");
      command = command0;
      command0 = strtok(NULL, " ");
      cmd.command2 = command0;
      command0 = strtok(NULL, " ");
      cmd.command3 = command0;
      command0 = strtok(NULL, " ");
      cmd.command4 = command0;

      for (int i = 0; i < commandCount; i++) {
        if (commandList[i] == command) {
          pFunctions[i](cmd);
        }
      }

      if (command == "") {
        // Skip
      } else if (command == "?") {
        //
      } else if (command == "RESET") {
        ESP.restart();
      }

      _serial->println(">");
    }
  };

  static void resetCommand(command_t command) {
    ESP.restart();
  };
};

#endif
