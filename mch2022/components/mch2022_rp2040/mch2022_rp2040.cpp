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
  this->interrupt_pin_->setup();
}

void Mch2022_rp2040Component::dump_config() {
  ESP_LOGCONFIG(TAG, "mch2022_rp2040:");
  LOG_I2C_DEVICE(this);

  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with the rp2040 failed!");
  }
  LOG_PIN("  Interrupt Pin: ", this->interrupt_pin_);
}

void Mch2022_rp2040Component::loop() {
    if (!this->interrupt_pin_->digital_read()) {
      uint8_t reg1 = 0;
      bool stop = true;
      this->read_register(RP2040_REG_INPUT1, &reg1, 2, stop);
      this->write_register(RP2040_REG_INTERRUPT2, 0x00, 1, stop);
    // uint8_t reg2 = this->read_register(RP2040_REG_INPUT1, &port, 1);
    // ESP_LOGE(TAG, "Button pressed on the rp2040 !");
      ESP_LOGE(TAG, "Reg1: %i", reg1);
    }
    // ESP_LOGE(TAG, "Reg2: %i", (int) reg2);
    // if (!this->interrupt_pin_->digital_read()) {
    // if {

    //  ESP_LOGE(TAG, "Button pressed on the rp2040 !");
    //}
    // this->interrupt_pin->clear_interrupt()
}

//void Mch2022_rp2040Component::pin_mode(uint8_t pin, gpio::Flags mode) {
//  uint8_t port = 0;
//
//  this->read_register(RP2040_REG_GPIO_DIR, &port, 1);
//
//  if (mode == gpio::FLAG_INPUT) {
//    port = port | (1 << (pin - 10));
//  } else if (mode == gpio::FLAG_OUTPUT) {
//    port = port & (~(1 << (pin - 10)));
//  }
//
//  this->write_register(RP2040_REG_GPIO_DIR, &port, 1);
//
//}

//void Mch2022_rp2040GPIOPin::setup() { this->pin_mode(this->flags_); }

//std::string Mch2022_rp2040GPIOPin::dump_summary() const { return str_snprintf("%u via Mch2022 RP2040", 15, this->pin_); }

// void Mch2022_rp2040GPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
// bool Mch2022_rp2040GPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
// void Mch2022_rp2040GPIOPin::digital_write(bool value) { this->parent_->digital_write(this->pin_, value != this->inverted_); }

}  // namespace mch2022_rp2040
}  // namespace esphome
