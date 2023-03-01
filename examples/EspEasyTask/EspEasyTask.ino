#include "EspEasyTask.h"

void loopTask() {
  uint32_t count = 0;
  while (1) {
    Serial.printf("loopTask count = %d\n", count);
    count++;
    delay(1000);
  }
}

void oneshotTask() {
  Serial.println("oneshotTask start");
  delay(1000);
  Serial.println("oneshotTask end");
}

EspEasyTask task;
EspEasyTask task2;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Task test");

  // Task begin
  //  task       : task function
  //  uxPriority : task priority(0[LOW]-24[HIGH])
  //               0  = Works only when delay() is called
  //               1  = same priority as loop()
  //               24 = strongest, delay() should be called periodically
  //  xCoreID    : core number
  //               PRO_CPU_NUM = wifi, ble
  //               APP_CPU_NUM = setup(), loop()
  task.begin(loopTask, 2, APP_CPU_NUM);
  task2.begin(oneshotTask);

  delay(3000);
  task.suspend();
  Serial.println("suspend");

  delay(3000);
  task.resume();
  Serial.println("resume");
}

void loop() {
}
