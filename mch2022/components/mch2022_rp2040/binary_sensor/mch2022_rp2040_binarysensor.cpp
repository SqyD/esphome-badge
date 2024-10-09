#include "mch2022_rp2040_binarysensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mch2022_rp2040 {

static const char *const TAG = "mch2022_rp2040.binary_sensor";

void Mch2022_rp2040BinarySensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up the MCH2022 Badge RP2040 binary sensors...");

}

void Mch2022_rp2040BinarySensor::dump_config() { LOG_BINARY_SENSOR("", "MCH2022 RP2040 Binary Sensor", this); }


}  // namespace mch2022_rp2040
}  // namespace esphome