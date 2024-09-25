#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace mch2022_rp2040 {

// A selection of registers as listed in the template app here
// https://github.com/badgeteam/esp32-component-mch2022-rp2040/blob/master/include/rp2040.h
// and in the rp2040 firmware here:
// https://github.com/badgeteam/mch2022-firmware-rp2040/blob/master/i2c_peripheral.h


// #define GPIO_INT_RP2040  34  // Active low


enum {
  RP2040_REG_GPIO_DIR = 0x01,
  RP2040_REG_GPIO_IN= 0x02,
  RP2040_REG_GPIO_OUT = 0x03,
  RP2040_REG_LCD_BACKLIGHT = 0x04,
  RP2040_REG_INPUT1 = 0x06,
  RP2040_REG_INPUT2 = 0x07,
  RP2040_REG_INTERRUPT1 = 0x08,
  RP2040_REG_INTERRUPT2 = 0x09
};

class Mch2022_rp2040Component : public Component, public i2c::I2CDevice {
 public:
  bool digital_read(uint8_t pin);
  bool button_read(uint8_t button);

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }
};


}  // namespace mch2022_rp2040
}  // namespace esphome