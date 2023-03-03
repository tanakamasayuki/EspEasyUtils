#include "EspEasyGPIOInterrupt.h"

void gpioInt1Task() {
  Serial.println("gpioInt1");
}

EspEasyGPIOInterrupt gpioInt1;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("GPIOInterrupt test");

  // Set Input Mode(INPUT or INPUT_PULLDOWN or INPUT_PULLUP)
  pinMode(GPIO_NUM_39, INPUT);

  // Int setting
  //   task : void function()
  //   gpio : 0 - 39(ESP32)
  //   mode : RISING or FALLING or CHANGE
  //   core : APP_CPU_NUM or PRO_CPU_NUM
  gpioInt1.begin(gpioInt1Task, GPIO_NUM_39, FALLING);
}

void loop() {
}
