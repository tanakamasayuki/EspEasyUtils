#include "EspEasyLED.h"

EspEasyLED led(GPIO_NUM_27, 25, 40);
// gpio          : 27
// led_num       : 1-
// maxBrightness : 1(dark)-255(bright). If it is too bright, it will be damaged by heat.

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Task test");
}

void loop() {
  // All RED
  //led.showColor(EspEasyLED::RED);
  led.showColor(255, 0, 0);
  delay(1000);

  // All GREEN
  led.showColor(EspEasyLEDColor::GREEN);
  delay(1000);

  // All BLUE
  led.showColor(EspEasyLEDColor::BLUE);
  delay(1000);

  // All WHITE
  led.showColor(EspEasyLEDColor::WHITE);
  delay(1000);

  // fade out 100(MAX) to 0(MIN)
  for (int i = 100; 0 <= i; i--) {
    led.setBrightness(i);
    led.show();
  }
  delay(1000);

  // fade in 0(MIN) to 100(MAX)
  for (int i = 0; i <= 100; i++) {
    led.setBrightness(i);
    led.show();
  }
  delay(1000);

  // Num access
  for (int i = 0; i < led.getLedNum(); i++) {
    led.setColor(i, EspEasyLEDColor::BLACK);
    led.show();
    delay(50);
  }
  delay(1000);
}
