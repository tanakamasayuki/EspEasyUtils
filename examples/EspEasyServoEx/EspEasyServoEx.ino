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
  Serial.println("p=0, spped=100");
  while (servo.getPosition() != 0) {
    Serial.printf("target=%d, position=%d\n", servo.getTarget(), servo.getPosition());
    delay(100);
  }
  delay(1000);

  servo.setSpeed(50);
  servo.setTarget(180);
  Serial.println("p=180, spped=50");
  while (servo.getPosition() != 180) {
    Serial.printf("target=%d, position=%d\n", servo.getTarget(), servo.getPosition());
    delay(100);
  }
  delay(1000);

  servo.setTarget(0, 100);
  Serial.println("p=0, spped=100");
  while (servo.getPosition() != 0) {
    Serial.printf("target=%d, position=%d\n", servo.getTarget(), servo.getPosition());
    delay(100);
  }
  delay(1000);

  servo.setTarget(90, 10);
  Serial.println("p=90, spped=10");
  while (servo.getPosition() != 90) {
    Serial.printf("target=%d, position=%d\n", servo.getTarget(), servo.getPosition());
    delay(100);
  }
  delay(1000);
}
