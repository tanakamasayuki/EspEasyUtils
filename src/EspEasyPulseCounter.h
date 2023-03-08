#ifndef __EspEasyPulseCounter_H__
#define __EspEasyPulseCounter_H__

#include "Arduino.h"
#include <driver/pcnt.h>
#include <soc/pcnt_struct.h>

class EspEasyPulseCounter {
public:
  pcnt_isr_handle_t _isrHandle;
  pcnt_unit_t _unit;
  gpio_num_t _gpio1;
  gpio_num_t _gpio2;
  uint16_t _roundCount;
  int16_t _counter;

  EspEasyPulseCounter(pcnt_unit_t unit, gpio_num_t gpio1, gpio_num_t gpio2, uint16_t roundCount) {
    _unit = unit;
    _gpio1 = gpio1;
    _gpio2 = gpio2;
    _roundCount = roundCount;
    _counter = 0;

    pinMode(_gpio1, INPUT);
    pinMode(_gpio2, INPUT);

    pcnt_config_t pcnt_config1 = {};
    pcnt_config1.pulse_gpio_num = _gpio1;
    pcnt_config1.ctrl_gpio_num = _gpio2;
    pcnt_config1.lctrl_mode = PCNT_MODE_KEEP;
    pcnt_config1.hctrl_mode = PCNT_MODE_REVERSE;
    pcnt_config1.pos_mode = PCNT_COUNT_INC;
    pcnt_config1.neg_mode = PCNT_COUNT_DEC;
    pcnt_config1.counter_h_lim = _roundCount;
    pcnt_config1.counter_l_lim = -_roundCount;
    pcnt_config1.unit = _unit;
    pcnt_config1.channel = PCNT_CHANNEL_0;

    pcnt_config_t pcnt_config2 = {};
    pcnt_config2.pulse_gpio_num = _gpio2;
    pcnt_config2.ctrl_gpio_num = _gpio1;
    pcnt_config2.lctrl_mode = PCNT_MODE_REVERSE;
    pcnt_config2.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config2.pos_mode = PCNT_COUNT_INC;
    pcnt_config2.neg_mode = PCNT_COUNT_DEC;
    pcnt_config2.counter_h_lim = _roundCount;
    pcnt_config2.counter_l_lim = -_roundCount;
    pcnt_config2.unit = _unit;
    pcnt_config2.channel = PCNT_CHANNEL_1;

    pcnt_unit_config(&pcnt_config1);
    pcnt_unit_config(&pcnt_config2);

    pcnt_event_enable(_unit, PCNT_EVT_H_LIM);
    pcnt_event_enable(_unit, PCNT_EVT_L_LIM);

    pcnt_counter_pause(_unit);
    pcnt_counter_clear(_unit);
    pcnt_counter_resume(_unit);

    pcnt_isr_register(_pcntIntr, this, 0, &_isrHandle);
    pcnt_intr_enable(_unit);
  };

  static void ARDUINO_ISR_ATTR _pcntIntr(void *arg) {
    EspEasyPulseCounter *pcnt = (EspEasyPulseCounter *)arg;
    if (PCNT.status_unit[pcnt->_unit].h_lim_lat) {
      pcnt->_counter++;
    } else if (PCNT.status_unit[pcnt->_unit].l_lim_lat) {
      pcnt->_counter--;
    }
    PCNT.int_clr.val = BIT(pcnt->_unit);
  };

  int16_t getIntrValue() {
    return _counter;
  };

  int16_t getValue() {
    int16_t value;
    pcnt_get_counter_value(_unit, &value);
    return value;
  };

  void clear() {
    pcnt_counter_clear(_unit);
    _counter = 0;
  };
};

#endif
