import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_INPUT,
    CONF_INVERTED,
    CONF_MODE,
    CONF_NUMBER,
    CONF_OUTPUT,
)
from esphome import pins

DEPENDENCIES = ["i2c"]
CODEOWNERS = ["@SqyD"]

MULTI_CONF = True

CONF_MCH20222_RP2040 = "mch2022_rp2040"

mch2022_rp2040_ns = cg.esphome_ns.namespace("mch2022_rp2040")

Mch2022_rp2040Component = mch2022_rp2040_ns.class_("Mch2022_rp2040Component", cg.Component, i2c.I2CDevice)
#Mch2022_rp2040GPIOPin = mch2022_rp2040_ns.class_("Mch2022_rp2040GPIOPin", cg.GPIOPin)

CONFIG_SCHEMA = (
    cv.Schema({cv.Required(CONF_ID): cv.declare_id(Mch2022_rp2040Component)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x17))
    .extend( { cv.Optional(CONF_INTERRUPT_PIN, default="34"): pins.internal_gpio_input_pin_schema })
)

async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID],
        config[CONF_INTERRUPT_PIN]
        )
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

#def validate_mode(mode):
#    if not (mode[CONF_INPUT] or mode[CONF_OUTPUT]) or (
#        mode[CONF_INPUT] and mode[CONF_OUTPUT]
#    ):
#        raise cv.Invalid("Mode must be either a input or a output")
#    return mode


#def validate_pin(pin):
#    if pin > 29:
#        raise cv.Invalid(f"pin {pin} doesn't exist")
#    return pin

#CH20222_RP2040_PIN_SCHEMA = cv.All(
#    {
#        cv.GenerateID(): cv.declare_id(Mch2022_rp2040GPIOPin),
#        cv.Required(CONF_MCH20222_RP2040): cv.use_id(Mch2022_rp2040Component),
#        cv.Required(CONF_NUMBER): cv.All(cv.int_range(min=0, max=29), validate_pin),
#        cv.Optional(CONF_MODE, default={}): cv.All(
#            {
#                cv.Optional(CONF_INPUT, default=False): cv.boolean,
#                cv.Optional(CONF_OUTPUT, default=False): cv.boolean,
#            },
#            validate_mode,
#        ),
#        cv.Optional(CONF_INVERTED, default=False): cv.boolean,
#    }
#3)

#@pins.PIN_SCHEMA_REGISTRY.register(CONF_MCH20222_RP2040, CH20222_RP2040_PIN_SCHEMA)
#async def mch2022_rp2040_pin_to_code(config):
#    var = cg.new_Pvariable(config[CONF_ID])
#    parent = await cg.get_variable(config[CONF_MCH20222_RP2040])
#
#    cg.add(var.set_parent(parent))
#    cg.add(var.set_pin(config[CONF_NUMBER]))
#    cg.add(var.set_inverted(config[CONF_INVERTED]))
#    cg.add(var.set_flags(pins.gpio_flags_expr(config[CONF_MODE])))
#
#   return var