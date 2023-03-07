#ifndef __EspEasyPWM_H__
#define __EspEasyPWM_H__

#include "Arduino.h"
#include <hal/ledc_types.h>

class EspEasyPWM {
public:
  ledc_channel_t _ledc;
  gpio_num_t _gpio;
  uint16_t _frequency;
  uint8_t _bit;

  EspEasyPWM(ledc_channel_t ledc, gpio_num_t gpio, uint16_t frequency = 12000, uint8_t bit = 8) {
    _ledc = ledc;
    _gpio = gpio;
    _frequency = frequency;
    _bit = bit;

    ledcSetup(_ledc, _frequency, _bit);
    ledcAttachPin(_gpio, _ledc);
  };

  void setPWM(uint8_t percent) {
    ledcWrite(_ledc, (1 << _bit) * percent / 100);
  }
};

#endif
