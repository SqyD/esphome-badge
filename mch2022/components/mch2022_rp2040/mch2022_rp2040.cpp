#include "mch2022_rp2040.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mch2022_rp2040 {

static const char *const TAG = "mch2022_rp2040";

void Mch2022_rp2040Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up the MCH2022 Badge RP2040 io expander component...");

  // Can we read an input register?
  uint8_t port = 0;
  if (this->read_register(RP2040_REG_INPUT1, &port, 1) != i2c::ERROR_OK) {
    this->mark_failed();
    return;
  }
}

void Mch2022_rp2040Component::dump_config() {
  ESP_LOGCONFIG(TAG, "mch2022_rp2040:");
  LOG_I2C_DEVICE(this);

  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with the rp2040 failed!");
  }
}

bool Mch2022_rp2040Component::digital_read(uint8_t pin) {
  bool state = false;
  uint8_t port = 0;

  if (this->read_register(RP2040_REG_GPIO_IN, &port, 1) != i2c::ERROR_OK) {
    this->status_set_warning();
    return state;
  }

    state = (port & (1 << pin)) != 0;
  }

  this->status_clear_warning();
  return state;
}

bool Mch2022_rp2040Component::button_read(uint8_t button) {
  bool state = false;
  uint8_t port = 0;

  if (button > 7) {
    if (this->read_register(RP2040_REG_INPUT2, &port, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return state;
    }

    state = (port & (1 << (button - 10))) != 0;
  } else {
    if (this->read_register(RP2040_REG_INPUT1, &port, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return state;
    }

    *state = (port >> pin) & 0x01;
  }

  this->status_clear_warning();
  return state;
}

