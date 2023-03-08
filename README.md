# ESP32 Easy Utils

A handy set of tools.

## EspEasySerialCommand

Serial can be used to create interactive tools.

```c
#include "EspEasySerialCommand.h"

EspEasySerialCommand command(Serial);

void setup() {
  command.addCommand("RESET", [](EspEasySerialCommand::command_t) {
    ESP.restart();
  });

  command.addCommand("WIFI", [](EspEasySerialCommand::command_t) {
    WiFi.begin(command.command2.c_str(), command.command3.c_str());
  });
}

void loop() {
  command.task();
}
```

## EspEasyTask

FreeRTOS Task Utilities.

```c
#include "EspEasyTask.h"

void loopTask() {
  uint32_t count = 0;
  while (1) {
    Serial.printf("loopTask count = %d\n", count);
    count++;
    delay(1000);
  }
}

EspEasyTask task;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Task test");

  task.begin(loopTask, 2, APP_CPU_NUM);
}

void loop() {
}
```

## EspEasyQueue

FreeRTOS Queue Utilities.

```c
#include "EspEasyQueue.h"
#include "EspEasyTask.h"

typedef struct {
  uint32_t time;
  uint8_t val;
} queue_data_t;

EspEasyQueue queue1;
EspEasyTask task1;

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

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Queue test");

  queue1.create(10, sizeof(queue_data_t));

  task1.begin(loopTask1);
}

void loop() {
    queue_data_t data;
    data.time = millis();
    data.val = random(0, 256);

    queue1.send(&data);

    delay(1000);
}
```

## EspEasyTimer

ESP32 hardware timer Utilities.

```c
#include "EspEasyTimer.h"

void timer1Task() {
  Serial.println("timer1");
}

// Max Timer ESP32=4, ESP32-S3=4, ESP32-C2=1, ESP32-C3=2, ESP32-C6=2 
EspEasyTimer timer1(TIMER_GROUP_0, TIMER_0);              // Dual core=APP_CPU_NUM(core1), Single Core=PRO_CPU_NUM(core0)

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Timer test");

  timer1.begin(timer1Task, 1000);
}

void loop() {
}
```

## EspEasyGPIOInterrupt

```c
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
```

## EspEasyLED

```c
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
  //led.showColor(EspEasyLEDColor::RED);
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
```

## EspEasyPWM

```c
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
```

## EspEasyServo(Simple)

```c
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
  delay(5000);

  servo.setServo(0);
  delay(5000);

  servo.setServo(180);
  delay(5000);

  for (int i = 0; i <= 180; i++) {
    servo.setServo(i);
    delay(30);
  }
}
```

## EspEasyServoEx(Speed setting)

```c
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
```
