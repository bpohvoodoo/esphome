#include "ds3502.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ds3502 {

static const char *const TAG = "DS3502";

void DS3502::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DS3502 (0x%02X)...", this->address_);
  auto err = this->write(nullptr, 0);
  if (err != i2c::ERROR_OK) {
    this->error_code_ = COMMUNICATION_FAILED;
    this->mark_failed();
    return;
  }
  this->write_byte(DS3502_MODE, 0x80);
}

void DS3502::dump_config() {
  ESP_LOGCONFIG(TAG, "Communication with DS3502 succeeded!");    
  LOG_I2C_DEVICE(this);

  if (this->error_code_ == COMMUNICATION_FAILED) {
    ESP_LOGE(TAG, "Communication with DS3502 failed!");
  }
}

float DS3502::get_state(void) {
  uint8_t value;
  this->read_byte(DS3502_WIPER, &value);
  return (float)(value / (pow(2, DS3502_RES) - 1));
}

void DS3502::write_state(float state) {
  const uint8_t value = (uint8_t) round(state * (pow(2, DS3502_RES) - 1));
  ESP_LOGCONFIG(TAG, "Setting DS3502 Potentiometer to value of %i", value);
  this->write_byte(DS3502_WIPER, value);
  //delay(10);
  //ESP_LOGCONFIG(TAG, "Checking DS3502 Potentiometer value of %f", this->get_state() * 100);
}

void DS3502::set_initial_value(float initial_value) {
  const uint8_t value = (uint8_t) round(initial_value * (pow(2, DS3502_RES) - 1));
  ESP_LOGCONFIG(TAG, "Setting up DS3205 Potentiometer with initial value of %i", value);
  this->write_byte(DS3502_MODE, 0x00);
  this->write_byte(DS3502_WIPER, value);
  delay(100);
  this->write_byte(DS3502_MODE, 0x80);
}
}
}