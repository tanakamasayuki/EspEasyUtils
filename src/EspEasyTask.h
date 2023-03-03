#ifndef __EspEasyTask_H__
#define __EspEasyTask_H__

#ifndef CONFIG_FREERTOS_UNICORE
#define ESP_EASY_TASK_CPU_NUM APP_CPU_NUM
#else
#define ESP_EASY_TASK_CPU_NUM PRO_CPU_NUM
#endif

class EspEasyTask {
public:
  EspEasyTask() {
    _taskHandle = NULL;
  }

  static void _task(void *pvParameters) {
    EspEasyTask *task = (EspEasyTask *)pvParameters;
    task->pTask();
    vTaskDelete(NULL);
    task->_taskHandle = NULL;
  };

  void (*pTask)();
  TaskHandle_t _taskHandle;

  void begin(void (*task)(), UBaseType_t uxPriority = 2, BaseType_t xCoreID = ESP_EASY_TASK_CPU_NUM) {
    if (_taskHandle != NULL) {
      vTaskDelete(_taskHandle);
    }

    pTask = task;
    xTaskCreateUniversal(
      _task,
      "",
      8192,
      this,
      uxPriority,
      &_taskHandle,
      xCoreID);
  };

  void suspend() {
    if (_taskHandle) {
      vTaskSuspend(_taskHandle);
    }
  };

  void resume() {
    if (_taskHandle) {
      vTaskResume(_taskHandle);
    }
  };
};

#endif
