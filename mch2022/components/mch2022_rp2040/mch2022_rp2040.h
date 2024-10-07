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

enum {
    RP2040_INPUT_BUTTON_HOME = 0,
    RP2040_INPUT_BUTTON_MENU,
    RP2040_INPUT_BUTTON_START,
    RP2040_INPUT_BUTTON_ACCEPT,
    RP2040_INPUT_BUTTON_BACK,
    RP2040_INPUT_FPGA_CDONE,
    RP2040_INPUT_BATTERY_CHARGING,
    RP2040_INPUT_BUTTON_SELECT,
    RP2040_INPUT_JOYSTICK_LEFT,
    RP2040_INPUT_JOYSTICK_PRESS,
    RP2040_INPUT_JOYSTICK_DOWN,
    RP2040_INPUT_JOYSTICK_UP,
    RP2040_INPUT_JOYSTICK_RIGHT
};

class Mch2022_rp2040Component : public Component, public i2c::I2CDevice {
 public:
  void pin_mode(uint8_t pin, gpio::Flags mode);
  void setup() override;
  void dump_config() override;
  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }
  void loop() override;
  float get_setup_priority() const override { return setup_priority::IO; }

 protected:
   InternalGPIOPin *interrupt_pin_{};
};

//class Mch2022_rp2040GPIOPin : public GPIOPin {
// public:
//  void set_parent(Mch2022_rp2040Component *parent) { this->parent_ = parent; }
//  void set_pin(uint8_t pin) { this->pin_ = pin; }
//  void set_inverted(bool inverted) { this->inverted_ = inverted; }
//  void set_flags(gpio::Flags flags) { this->flags_ = flags; }

//  void setup() override;
//  std::string dump_summary() const override;
//  void pin_mode(gpio::Flags flags) override;
//  bool digital_read() override;
//  void digital_write(bool value) override;
//
// protected:
//  Mch2022_rp2040Component *parent_;
//
//  uint8_t pin_;
//  bool inverted_;
//  gpio::Flags flags_;
// };


}  // namespace mch2022_rp2040
}  // namespace esphome