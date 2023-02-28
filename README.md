# ESP32 Easy Utils

A handy set of tools.

## EspEasySerialCommand

Serial can be used to create interactive tools.

```c
#include "EspEasySerialCommand.h"

EspEasySerialCommand command(Serial);

void setup() {
  command.addCommand("RESET", EspEasySerialCommand::resetCommand);
}

void loop() {
  command.task();
}
```
