#include "mch2022_badgeros.h"
#include "esphome/core/log.h"
#include <string>


namespace esphome {
namespace mch2022_badgeros {

static const char *const TAG = "mch2022_badgeros";

void Mch2022_BadgerosComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up the MCH2022 BadgerOS component...");
  if (this->use_badgeros_wifi_) {
    nvs_handle_t handle;
    size_t required_size;
    nvs_open("system", NVS_READWRITE, &handle); 
    nvs_get_str(handle, "wifi.ssid", NULL, &required_size);
    char *ssid = (char*)malloc(required_size);
    nvs_get_str(handle, "wifi.ssid", ssid, &required_size);
    std::string strssid = ssid;
    nvs_get_str(handle, "wifi.password", NULL, &required_size);
    char *password = (char*)malloc(required_size);
    nvs_get_str(handle, "wifi.password", password, &required_size);
    std::string strpassword = password;
    nvs_close(handle);
    ESP_LOGD(TAG, "Retrieved Wi-Fi settings from NVS, ssid=%s, password=" LOG_SECRET("%s"), strssid.c_str(), strpassword.c_str());
    wifi::WiFiAP sta{};
    sta.set_ssid(ssid);
    sta.set_password(password);
    wifi::global_wifi_component->set_sta(sta);
    wifi::global_wifi_component->start_connecting(sta, false);
  }
}
void Mch2022_BadgerosComponent::use_badgeros_wifi(bool use_badgeros_wifi) { this->use_badgeros_wifi_ = use_badgeros_wifi; }

void Mch2022_BadgerosComponent::dump_config() { ESP_LOGCONFIG(TAG, "mch2022_badgeros:"); }

}  // namespace mch2022_badgeros
}  // namespace esphome