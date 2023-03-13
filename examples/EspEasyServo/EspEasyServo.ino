#include "EspEasyServo.h"

EspEasyServo servo(LEDC_CHANNEL_0, GPIO_NUM_2);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Servo test");
}

void loop() {
  // set 0(min)-90(center)-180(max)
  servo.setServo(90);
  delay(2000);

  servo.setServo(0);
  delay(2000);

  servo.setServo(180);
  delay(2000);

  for (int i = 0; i <= 180; i++) {
    servo.setServo(i);
    delay(30);
  }
}
