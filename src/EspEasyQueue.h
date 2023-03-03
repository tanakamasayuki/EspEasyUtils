#ifndef __EspEasyQueue_H__
#define __EspEasyQueue_H__

class EspEasyQueue {
public:
  QueueHandle_t _queue;

  void create(UBaseType_t uxQueueLength, UBaseType_t uxItemSize) {
    _queue = xQueueCreate(uxQueueLength, uxItemSize);
  };

  bool send(void *data, TickType_t xTicksToWait = 0) {
    return xQueueSend(_queue, data, xTicksToWait);
  };

  bool sendFromISR(void *data) {
    return xQueueSendFromISR(_queue, data, 0);
  };

  bool receiveWait(void *data, TickType_t xTicksToWait = portMAX_DELAY) {
    return xQueueReceive(_queue, data, xTicksToWait);
  };

  bool receiveNoWait(void *data) {
    return receiveWait(data, 0);
  };
};

#endif
