#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/core/hal.h"
#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

static const uint8_t DS3502_ADDR = 0x28;

static const uint8_t DS3502_WIPER = 0x00;  // < Wiper value register
static const uint8_t DS3502_MODE  = 0x02;  // < Mode selection register
static const uint8_t DS3502_RES   = 7;

namespace esphome {
namespace ds3502 {

class DS3502 : public Component, public output::FloatOutput, public i2c::I2CDevice {
 public:
  void setup();
  void dump_config() override;
  
  float get_state(void);
  void write_state(float state) override;
  void set_initial_value(float initial_value);

 protected:
  enum ErrorCode { NONE = 0, COMMUNICATION_FAILED } error_code_{NONE};
};

}  // namespace ds3502
}  // namespace esphome