#include "EspEasyTimer.h"

void timer1Task() {
  Serial.println("timer1");
}
void timer2Task() {
  Serial.println("timer2");
}
void timer3Task() {
  Serial.println("timer3");
}

// Max Timer ESP32=4, ESP32-S3=4, ESP32-C2=1, ESP32-C3=2, ESP32-C6=2 
EspEasyTimer timer1(TIMER_GROUP_0, TIMER_0);              // Dual core=APP_CPU_NUM(core1), Single Core=PRO_CPU_NUM(core0)
EspEasyTimer timer2(TIMER_GROUP_0, TIMER_1, APP_CPU_NUM); // APP_CPU_NUM(core1)
EspEasyTimer timer3(TIMER_GROUP_1, TIMER_0, PRO_CPU_NUM); // PRO_CPU_NUM(core0)

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Timer test");

  // Timer begin
  //  timerTask  : task function
  //  ms         : millisecond interval
  timer1.begin(timer1Task, 1000);
  timer2.begin(timer2Task, 2000);
  timer3.begin(timer3Task, 3000);
}

void loop() {
  delay(1);
}
