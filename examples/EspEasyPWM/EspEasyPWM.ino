#include "EspEasyPWM.h"

EspEasyPWM pwn(LEDC_CHANNEL_0, GPIO_NUM_2);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("PWM test");
}

void loop() {
  // set 0%-100%
  pwn.setPWM(100);
  delay(1000);

  pwn.setPWM(0);
  delay(1000);

  pwn.setPWM(50);
  delay(1000);

  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 100; i++) {
      pwn.setPWM(i);
      delay(5);
    }
  }

  pwn.setPWM(0);
  delay(1000);
}
