#ifndef __EspEasyServoEx_H__
#define __EspEasyServoEx_H__

#include "Arduino.h"
#include <hal/ledc_types.h>

#ifndef CONFIG_FREERTOS_UNICORE
#define ESP_EASY_SERVO_TASK_CPU_NUM APP_CPU_NUM
#else
#define ESP_EASY_SERVO_TASK_CPU_NUM PRO_CPU_NUM
#endif

class EspEasyServoEx {
public:
  ledc_channel_t _ledc;
  gpio_num_t _gpio;
  uint16_t _frequency;
  uint8_t _bit;
  uint16_t _min;
  uint16_t _max;
  TaskHandle_t _taskHandle;
  float _target;
  float _position;
  uint8_t _speed;
  float _d;

  EspEasyServoEx(ledc_channel_t ledc, gpio_num_t gpio, uint8_t initPosition = 90) {
    _ledc = ledc;
    _gpio = gpio;
    _frequency = 50;
    _bit = 10;
    _min = ((0.5 / 20) * (1 << _bit)) + 0.5;  // (0.5ms/20ms)*1024 + 0.5(round)
    _max = ((2.4 / 20) * (1 << _bit)) + 0.5;  // (2.4ms/20ms)*1024 + 0.5(round)
    _speed = 100;

    ledcSetup(_ledc, _frequency, _bit);
    ledcAttachPin(_gpio, _ledc);

    _position = initPosition;
    _target = initPosition;
    ledcWrite(_ledc, (_max - _min) * initPosition / 180);

    xTaskCreateUniversal(
      _task,
      "",
      8192,
      this,
      24,
      &_taskHandle,
      ESP_EASY_SERVO_TASK_CPU_NUM);
  };

  static void _task(void *pvParameters) {
    EspEasyServoEx *servo = (EspEasyServoEx *)pvParameters;
    servo->_update();
  };

  void _update() {
    while (1) {
      if (_position != _target) {
        float newPosition;
        if (_position < _target) {
          // + Move
          if (_d < (_target - _position)) {
            newPosition = _position + _d;
          } else {
            newPosition = _target;
          }
        } else {
          // - Move
          if (_d < (_position - _target)) {
            newPosition = _position - _d;
          } else {
            newPosition = _target;
          }
        }
        ledcWrite(_ledc, (_max - _min) * newPosition / 180);
        _position = newPosition;
      }
      delay(10);
    }
  };

  void setTarget(uint8_t degree, uint8_t speed = 0) {
    if (180 < degree) {
      degree = 90;
    }
    if (speed != 0) {
      setSpeed(speed);
    }

    _target = degree;
  }

  void setSpeed(uint8_t speed) {
    if (speed != 0) {
      _speed = speed;
      _d = 2.0 * _speed / 100;
    }
  }
};

#endif
