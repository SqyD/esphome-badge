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

  this->status_clear_warning();
  return state;
}

void Mch2022_rp2040Component::digital_write(uint8_t pin, bool value) {
  uint8_t port = 0;
  uint8_t register_data = 0;

  if (pin > 7) {
    if (this->read_register(RP2040_REG_GPIO_IN, &register_data, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return;
    }

    register_data = register_data & (~(1 << (pin - 10)));
    port = register_data | value << (pin - 10);

    if (this->write_register(RP2040_REG_GPIO_OUT, &port, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return;
    }
  } else {
    if (this->read_register(RP2040_REG_GPIO_OUT, &register_data, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return;
    }
    register_data = register_data & (~(1 << pin));
    port = register_data | value << pin;

    if (this->write_register(RP2040_REG_GPIO_OUT, &port, 1) != i2c::ERROR_OK) {
      this->status_set_warning();
      return;
    }
  }

  this->status_clear_warning();
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

    state = (port >> button) & 0x01;
  }

  this->status_clear_warning();
  return state;
}

void Mch2022_rp2040Component::pin_mode(uint8_t pin, gpio::Flags mode) {
  uint8_t port = 0;


  this->read_register(RP2040_REG_GPIO_DIR, &port, 1);

  if (mode == gpio::FLAG_INPUT) {
    port = port | (1 << (pin - 10));
  } else if (mode == gpio::FLAG_OUTPUT) {
    port = port & (~(1 << (pin - 10)));
  }

  this->write_register(RP2040_REG_GPIO_DIR, &port, 1);

}

void Mch2022_rp2040GPIOPin::setup() { this->pin_mode(this->flags_); }

std::string Mch2022_rp2040GPIOPin::dump_summary() const { return str_snprintf("%u via Mch2022 RP2040", 15, this->pin_); }

void Mch2022_rp2040GPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
bool Mch2022_rp2040GPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
void Mch2022_rp2040GPIOPin::digital_write(bool value) { this->parent_->digital_write(this->pin_, value != this->inverted_); }

}  // namespace mch2022_rp2040
}  // namespace esphome
