#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/mch2022_rp2040/mch2022_rp2040.h"
#include "esphome/core/component.h"

#include <vector>

namespace esphome {
namespace mch2022_rp2040 {

class Mch2022_rp2040BinarySensor : public Component, public binary_sensor::BinarySensor {
  public:
    void setup() override; 
    void dump_config() override;

};

}  // namespace mmch2022_rp2040
}  // namespace esphome