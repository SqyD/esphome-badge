#include "mch2022_badgeros.h"
#include "esphome/core/log.h"


namespace esphome {
namespace mch2022_badgeros {

static const char *const TAG = "mch2022_badgeros";

void Mch2022_BadgerosComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up the MCH2022 BadgerOS component...");
  if this->use_badgeros_wifi_ {
    nvs_handle_t handle;
    nvs_open("system", NVS_READWRITE, &handle); 
    nvs_get_str(handle, "wifi.ssid", NULL, &len);
    ssid = malloc(len);
    nvs_get_str(handle, "wifi.ssid", ssid, &len);
    res = nvs_get_str(handle, "wifi.password", NULL, &len);
    password = malloc(len);
    res = nvs_get_str(handle, "wifi.password", password, &len);
    wifi::WiFiAP sta{};
    sta.set_ssid(ssid);
    sta.set_password(password);
    this->connecting_sta_ = sta;
    wifi::global_wifi_component->set_sta(sta);
    wifi::global_wifi_component->start_connecting(sta, false);
    ESP_LOGD(TAG, "Retrieved Wi-Fi settings from NVS, ssid=%s, password=" LOG_SECRET("%s"), ssid.c_str(),
      password.c_str());
  }
}
void Mch2022_BadgerosComponent::use_badgeros_wifi(bool use_badgeros_wifi) { this->use_badgeros_wifi_ = use_badgeros_wifi; }

void Mch2022_BadgerosComponent::dump_config() { ESP_LOGCONFIG(TAG, "mch2022_badgeros:"); }