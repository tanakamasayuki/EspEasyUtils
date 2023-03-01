#ifndef __EspEasyTask_H__
#define __EspEasyTask_H__

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

#ifndef CONFIG_FREERTOS_UNICORE
  void begin(void (*task)(), UBaseType_t uxPriority = 2, BaseType_t xCoreID = APP_CPU_NUM) {
#else
  void begin(void (*task)(), UBaseType_t uxPriority = 2, BaseType_t xCoreID = PRO_CPU_NUM) {
#endif
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
