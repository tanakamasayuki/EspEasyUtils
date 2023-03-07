#include "EspEasyServoEx.h"

EspEasyServoEx servo(LEDC_CHANNEL_0, GPIO_NUM_2);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Servo test");
}

void loop() {
  // set 0(min)-90(center)-180(max), speed 1(min)-100(max)
  servo.setTarget(0, 100);
  delay(5000);

  servo.setSpeed(50);
  servo.setTarget(180);
  delay(5000);

  servo.setTarget(0, 100);
  delay(5000);

  servo.setTarget(90, 10);
  delay(5000);
}
