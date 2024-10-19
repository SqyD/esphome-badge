#pragma once

#include <nvs_flash.h>
#include <nvs.h>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/defines.h"
#include "esphome/components/wifi/wifi_component.h"



#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif

namespace esphome {
namespace mch2022_badgeros {

class Mch2022_BadgerosComponent : public Component {
  public:
    void use_badgeros_wifi(bool use_badgeros_wifi);
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::IO; }

  protected:
    bool use_badgeros_wifi_{true};
};


}  // namespace mch2022_badgeros
}  // namespace esphome