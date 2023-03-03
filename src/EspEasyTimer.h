#ifndef __EspEasyTimer_H__
#define __EspEasyTimer_H__

extern QueueHandle_t _EspEasyTimerQueue[4];
void IRAM_ATTR _EspEasyTimerOnTimer0();
void IRAM_ATTR _EspEasyTimerOnTimer1();
void IRAM_ATTR _EspEasyTimerOnTimer2();
void IRAM_ATTR _EspEasyTimerOnTimer3();

#ifndef CONFIG_FREERTOS_UNICORE
#define ESP_EASY_TIMER_CPU_NUM APP_CPU_NUM
#else
#define ESP_EASY_TIMER_CPU_NUM PRO_CPU_NUM
#endif

class EspEasyTimer {
public:
  static uint8_t _lastTimerId;
  uint8_t _timerId;
  hw_timer_t *_timer;
  void (*_timerTask)();
  TaskHandle_t _taskHandle;

  EspEasyTimer(BaseType_t xCoreID = ESP_EASY_TIMER_CPU_NUM) {
    _timerId = _lastTimerId;
    _lastTimerId++;

    if (SOC_TIMER_GROUP_TOTAL_TIMERS < _timerId) {
      ESP_LOGI("EspEasyTimer", "There are only %d timers. This is %d timers.", SOC_TIMER_GROUP_TOTAL_TIMERS, _timerId);
      return;
    }
    _EspEasyTimerQueue[_timerId] = xQueueCreate(1, 0);

    xTaskCreateUniversal(
      _waitTask,
      "",
      8192,
      this,
      24,
      &_taskHandle,
      xCoreID);

    _timer = timerBegin(_timerId, getApbFrequency() / 1000000, true);
    if (_timerId == 0) {
      timerAttachInterrupt(_timer, _EspEasyTimerOnTimer0, false);
    } else if (_timerId == 1) {
      timerAttachInterrupt(_timer, _EspEasyTimerOnTimer1, false);
    } else if (_timerId == 2) {
      timerAttachInterrupt(_timer, _EspEasyTimerOnTimer2, false);
    } else if (_timerId == 3) {
      timerAttachInterrupt(_timer, _EspEasyTimerOnTimer3, false);
    }
  }

  static void _waitTask(void *pvParameters) {
    EspEasyTimer *timer = (EspEasyTimer*)pvParameters;
    while (1) {
      xQueueReceive(_EspEasyTimerQueue[timer->_timerId], NULL, portMAX_DELAY);
      timer->_timerTask();
    }
  };

  void begin(void (*timerTask)(), uint32_t ms) {
    if (SOC_TIMER_GROUP_TOTAL_TIMERS < _timerId) {
      ESP_LOGI("EspEasyTimer", "There are only %d timers. This is %d timers.", SOC_TIMER_GROUP_TOTAL_TIMERS, _timerId);
      return;
    }

    _timerTask = timerTask;

    timerAlarmWrite(_timer, ms * 1000, true);
    timerAlarmEnable(_timer);
  };
};

#endif
