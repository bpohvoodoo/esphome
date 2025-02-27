import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import output, i2c
from esphome.const import (
    CONF_ID,
    CONF_INITIAL_VALUE,
)

DEPENDENCIES = ["i2c"]

ds3502 = cg.esphome_ns.namespace("ds3502")
DS3502 = ds3502.class_("DS3502", output.FloatOutput, cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    output.FLOAT_OUTPUT_SCHEMA.extend(
        {
            cv.Required(CONF_ID): cv.declare_id(DS3502),
            cv.Optional(CONF_INITIAL_VALUE, default=0.0): cv.float_range(
                min=0.0, max=1.0
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x28))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await output.register_output(var, config)
    
    cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))