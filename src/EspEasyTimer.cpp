#ifndef __EspEasyTimer_CPP__
#define __EspEasyTimer_CPP__

#include "Arduino.h"
#include "EspEasyTimer.h"

uint8_t EspEasyTimer::_lastTimerId = 0;

QueueHandle_t _EspEasyTimerQueue[4];

void IRAM_ATTR _EspEasyTimerOnTimer0() {
  xQueueSendFromISR(_EspEasyTimerQueue[0], NULL, 0);
};
void IRAM_ATTR _EspEasyTimerOnTimer1() {
  xQueueSendFromISR(_EspEasyTimerQueue[1], NULL, 0);
};
void IRAM_ATTR _EspEasyTimerOnTimer2() {
  xQueueSendFromISR(_EspEasyTimerQueue[2], NULL, 0);
};
void IRAM_ATTR _EspEasyTimerOnTimer3() {
  xQueueSendFromISR(_EspEasyTimerQueue[3], NULL, 0);
};

#endif
