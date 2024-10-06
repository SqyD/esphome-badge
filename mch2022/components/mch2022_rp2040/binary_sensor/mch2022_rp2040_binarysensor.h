#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/mch2022_rp2040/mch2022_rp2040.h"
#include "esphome/core/component.h"

#include <vector>

namespace esphome {
namespace mch2022_rp2040 {

class Mch2022_rp2040BinarySensor : public Component, public binary_sensor::BinarySensor, public SensorItem {
 public:
  void set_parent(Mch2022_rp2040Component *parent) { this->parent_ = parent; }
  void dump_config() override;
  void loop();

};

}  // namespace mmch2022_rp2040
}  // namespace esphome