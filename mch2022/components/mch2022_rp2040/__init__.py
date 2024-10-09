import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_INTERRUPT_PIN,
)
from esphome import pins

DEPENDENCIES = ["i2c"]
CODEOWNERS = ["@SqyD"]

MULTI_CONF = True

CONF_MCH20222_RP2040 = "mch2022_rp2040"

mch2022_rp2040_ns = cg.esphome_ns.namespace("mch2022_rp2040")

Mch2022_rp2040Component = mch2022_rp2040_ns.class_("Mch2022_rp2040Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema({cv.Required(CONF_ID): cv.declare_id(Mch2022_rp2040Component)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x17))
    .extend({cv.Optional(CONF_INTERRUPT_PIN): cv.All(pins.internal_gpio_input_pin_schema)})
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    interrupt_pin = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
    cg.add(var.set_pin(interrupt_pin))
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
