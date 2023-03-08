#ifndef __EspEasyTimer_H__
#define __EspEasyTimer_H__

#ifndef CONFIG_FREERTOS_UNICORE
#define ESP_EASY_TIMER_CPU_NUM APP_CPU_NUM
#else
#define ESP_EASY_TIMER_CPU_NUM PRO_CPU_NUM
#endif

#include <hal/timer_types.h>
#include <driver/timer.h>

class EspEasyTimer {
public:
  timer_group_t _timerGroup;
  timer_idx_t _timerIdx;
  uint8_t _timerId;
  void (*_timerTask)();
  TaskHandle_t _taskHandle;
  QueueHandle_t _queue;
  hw_timer_t *_timer;

  EspEasyTimer(timer_group_t timerGroup, timer_idx_t timerIdx, BaseType_t xCoreID = ESP_EASY_TIMER_CPU_NUM) {
    _timerGroup = timerGroup;
    _timerIdx = timerIdx;
    _timerId = _timerGroup + _timerIdx * 2;

    _queue = xQueueCreate(1, 0);

    xTaskCreateUniversal(
      _waitTask,
      "",
      8192,
      this,
      24,
      &_taskHandle,
      xCoreID);

    _timer = timerBegin(_timerId, getApbFrequency() / 1000000, true);
    timer_isr_callback_add(_timerGroup, _timerIdx, _onTimer, this, false);
  }

  static void _waitTask(void *pvParameters) {
    EspEasyTimer *timer = (EspEasyTimer *)pvParameters;
    while (1) {
      xQueueReceive(timer->_queue, NULL, portMAX_DELAY);
      timer->_timerTask();
    }
  };

  void begin(void (*timerTask)(), uint32_t ms) {
    _timerTask = timerTask;

    timerAlarmWrite(_timer, ms * 1000, true);
    timerAlarmEnable(_timer);
  };

  static bool ARDUINO_ISR_ATTR _onTimer(void *arg) {
    EspEasyTimer *timer = (EspEasyTimer *)arg;
    xQueueSendFromISR(timer->_queue, NULL, 0);
    return false;
  };
};

#endif
