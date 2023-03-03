#ifndef __EspEasyLED_H__
#define __EspEasyLED_H__

#include "Arduino.h"

class EspEasyLED {
public:
  struct color_t {
    uint8_t R;
    uint8_t G;
    uint8_t B;
  } __attribute__((packed));

  static color_t BLACK;
  static color_t NAVY;
  static color_t DARKGREEN;
  static color_t DARKCYAN;
  static color_t MAROON;
  static color_t PURPLE;
  static color_t OLIVE;
  static color_t LIGHTGREY;
  static color_t LIGHTGRAY;
  static color_t DARKGREY;
  static color_t DARKGRAY;
  static color_t BLUE;
  static color_t GREEN;
  static color_t CYAN;
  static color_t RED;
  static color_t MAGENTA;
  static color_t YELLOW;
  static color_t WHITE;
  static color_t ORANGE;
  static color_t GREENYELLOW;
  static color_t PINK;
  static color_t BROWN;
  static color_t GOLD;
  static color_t SILVER;
  static color_t SKYBLUE;
  static color_t VIOLET;

  gpio_num_t _gpio;
  uint16_t _ledNum;
  uint8_t _maxBrightness;
  uint8_t _brightness;
  color_t *_led;

  EspEasyLED(gpio_num_t gpio, uint16_t ledNum, uint8_t maxBrightness = 40) {
    _gpio = gpio;
    _ledNum = ledNum;
    _maxBrightness = maxBrightness;
    _brightness = 100;

    uint32_t buffSize = _ledNum * 3;
    _led = (color_t *)calloc(1, buffSize);
    if (_led == NULL) {
      ESP_LOGE("EspEasyLED", "calloc failed");
      return;
    }
  };

  // 0-100
  void setBrightness(uint8_t brightness) {
    _brightness = brightness;
  }

  uint8_t getBrightness() {
    return _brightness;
  }

  uint16_t getLedNum() {
    return _ledNum;
  }

  void setColor(uint16_t num, uint8_t r, uint8_t g, uint8_t b) {
    _led[num].R = r;
    _led[num].G = g;
    _led[num].B = b;
  };

  void setColor(uint16_t num, color_t color) {
    _led[num] = color;
  };

  void show() {
    for (int i = 0; i < _ledNum; i++) {
      neopixelWrite(_gpio,
                    _led[i].R * _brightness * _maxBrightness / 100 / 255,
                    _led[i].G * _brightness * _maxBrightness / 100 / 255,
                    _led[i].B * _brightness * _maxBrightness / 100 / 255);
      delayMicroseconds(100);
    }
    delay(1);
  };

  void showColor(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < _ledNum; i++) {
      _led[i].R = r;
      _led[i].G = g;
      _led[i].B = b;
    }
    show();
  };

  void showColor(color_t color) {
    for (int i = 0; i < _ledNum; i++) {
      _led[i] = color;
    }
    show();
  };

  void clear() {
    for (int i = 0; i < _ledNum; i++) {
      _led[i] = BLACK;
    }
    show();
  };
};

#endif
