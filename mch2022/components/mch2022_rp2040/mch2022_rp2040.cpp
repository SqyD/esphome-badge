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
  this->input_interrupt_ = false;
  this->input_state_ = 0x0000;
  this->update_inputs();
}

void Mch2022_rp2040Component::dump_config() {
  ESP_LOGCONFIG(TAG, "mch2022_rp2040:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with the rp2040 failed!");
  }
  LOG_PIN("  Interrupt Pin: ", this->interrupt_pin_);
}

#ifdef USE_BINARY_SENSOR
void Mch2022_rp2040Component::set_sub_binary_sensor(size_t input, binary_sensor::BinarySensor sens) {
// void Mch2022_rp2040Component::set_sub_binary_sensor(uint8_t input, binary_sensor::BinarySensor *sens) {
  // if (input < SubBinarySensorInput::SUB_BINARY_SENSOR_INPUT_COUNT) {
  this->sub_binary_sensors_[(size_t)input] = sens;
  //}
}

void Mch2022_rp2040Component::update_sub_binary_sensor_(size_t input, bool value) {
  // size_t index = (size_t) input;
  if (
    (this->sub_binary_sensors_[(size_t)input] != nullptr) && 
    ((!this->sub_binary_sensors_[(size_t)input]->has_state()) ||
    (this->sub_binary_sensors_[(size_t)input]->state != value))
    ) {
      this->sub_binary_sensors_[(size_t)input]->publish_state(value);
    }
}
#endif  // USE_BINARY_SENSOR

void Mch2022_rp2040Component::update_interrupt() {
  bool current_interrupt = !this->interrupt_pin_->digital_read();
  if (this->input_interrupt_ != current_interrupt) {
    this->input_interrupt_ = current_interrupt;
  }
}

void Mch2022_rp2040Component::update_inputs() {
  uint8_t input_register1 = 0x00;
  uint8_t input_register2 = 0x00;
  this->read_register(RP2040_REG_INPUT2, (uint8_t*) &input_register2, 4);
  this->read_register(RP2040_REG_INPUT1, (uint8_t*) &input_register1, 4);
  uint16_t state = ((input_register1 + (input_register2 << 8)) );
  if (this->input_state_ != state){
    this->input_state_ = state;
    ESP_LOGD(TAG, "Button state changed to %i", this->input_state_);
    for (uint8_t index = 0; index < 16; index++) {
        // std::string input_str = std::to_string(index);
        // input_str = SubBinarySensorInput(index)
        this->update_sub_binary_sensor_(index, (state >> index) & 0x01);
    }
  }
}
  
void Mch2022_rp2040Component::loop() {
  this->update_interrupt();
  if (this->input_interrupt_) {
    this->update_inputs();
  }
}

}  // namespace mch2022_rp2040
}  // namespace esphome
