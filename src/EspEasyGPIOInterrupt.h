#ifndef __EspEasyGPIOInterrupt_H__
#define __EspEasyGPIOInterrupt_H__

#ifndef CONFIG_FREERTOS_UNICORE
#define ESP_EASY_GPIO_INT_CPU_NUM APP_CPU_NUM
#else
#define ESP_EASY_GPIO_INT_CPU_NUM PRO_CPU_NUM
#endif

class EspEasyGPIOInterrupt {
public:
  QueueHandle_t _queue;
  TaskHandle_t _taskHandle;
  void (*_runTask)();

  static void ARDUINO_ISR_ATTR _isr(void *arg) {
    EspEasyGPIOInterrupt *gpioInt = (EspEasyGPIOInterrupt *)arg;
    xQueueSendFromISR(gpioInt->_queue, NULL, 0);
  };

  static void _waitTask(void *pvParameters) {
    EspEasyGPIOInterrupt *gpioInt = (EspEasyGPIOInterrupt *)pvParameters;
    while (1) {
      xQueueReceive(gpioInt->_queue, NULL, portMAX_DELAY);
      gpioInt->_runTask();
    }
  };

  void begin(void (*task)(), uint8_t pin, uint8_t mode, BaseType_t xCoreID = ESP_EASY_GPIO_INT_CPU_NUM) {
    _runTask = task;
    _queue = xQueueCreate(1, 0);

    xTaskCreateUniversal(
      _waitTask,
      "",
      8192,
      this,
      24,
      &_taskHandle,
      xCoreID);

      attachInterruptArg(pin, _isr, this, mode);
  };
};

#endif
