#include "mch2022_rp2040_binarysensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mch2022_rp2040 {

static const char *const TAG = "mch2022_rp2040.binary_sensor";

void Mch2022_rp2040BinarySensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up the MCH2022 Badge RP2040 binary sensors...");

  // Can we read an input register?
  uint8_t port = 0;
  if (this->parent_->read_register(RP2040_REG_INPUT1, &port, 1) != i2c::ERROR_OK) {
    this->mark_failed();
    return;
  }
}

void Mch2022_rp2040BinarySensor::dump_config() { LOG_BINARY_SENSOR("", "MCH2022 RP2040 Binary Sensor", this); }



void Mch2022_rp2040BinarySensor::loop() { 
    if (!this->interrupt_pin_->digital_read()) {

      ESP_LOGE(TAG, "Button pressed on the rp2040 !");
    }
}


}  // namespace mch2022_rp2040
}  // namespace esphome