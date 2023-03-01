#include "EspEasyQueue.h"
#include "EspEasyTask.h"

typedef struct {
  uint32_t time;
  uint8_t val;
} queue_data_t;

EspEasyQueue queue1;
EspEasyQueue queue2;
EspEasyTask task1;
EspEasyTask task2;

void loopTask1() {
  while (1) {
    queue_data_t data;
    // NoWait > process only what is in the queue
    while(queue1.receiveNoWait(&data)){
      Serial.printf("queue1 time=%d, val=%d\n",data.time, data.val);
    }
    delay(3000);
  }
}

void loopTask2() {
  while (1) {
    queue_data_t data;
    // Wait > Process queues in real time as they are added
    queue2.receiveWait(&data);
    Serial.printf("queue2 time=%d, val=%d\n",data.time, data.val);
    delay(1);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Queue test");

  queue1.create(10, sizeof(queue_data_t));
  queue2.create(10, sizeof(queue_data_t));

  task1.begin(loopTask1);
  task2.begin(loopTask2);
}

void loop() {
    queue_data_t data;
    data.time = millis();
    data.val = random(0, 256);

    queue1.send(&data);
    queue2.send(&data);

    delay(1000);
}
