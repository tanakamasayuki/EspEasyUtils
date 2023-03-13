#include "EspEasyPulseCounter.h"

const uint8_t inputPin = 26;
const uint8_t roundCount = 80;  // Number of counts per round

EspEasyPulseCounter pcnt(PCNT_UNIT_0, GPIO_NUM_0, GPIO_NUM_36, roundCount);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Pulse Counter test");

  pinMode(inputPin, INPUT);
}

void loop() {
  if (digitalRead(inputPin) == LOW) {
    pcnt.clear();
  }

  int16_t count = pcnt.getValue();
  int16_t intrCount = pcnt.getIntrValue();
  Serial.printf("pcnt %d %d %d\n", count, (count + 80) % 80, intrCount);
}
