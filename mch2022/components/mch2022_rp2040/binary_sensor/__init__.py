import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import binary_sensor
from esphome.const import CONF_ID
from .. import mch2022_rp2040_ns, Mch2022_rp2040Component, CONF_MCH20222_RP2040

DEPENDENCIES = ["mch2022_rp2040"]
CODEOWNERS = ["@SqyD"]

Mch2022_rp2040BinarySensor = mch2022_rp2040_ns.class_(
  "Mch2022_rp2040BinarySensor", cg.Component, binary_sensor.BinarySensor
)
CONF_INPUT = "input"

CONF_INPUTS = {
  "button_home": 0,
  "button_menu": 1,
  "button_start": 2,
  "button_accept": 3,
  "button_back": 4,
  "battery_charging": 6,
  "button_select": 7,
  "joystick_left": 8,
  "joystick_press": 9,
  "joystick_down": 10,
  "joystick_up": 11,
  "joystick_right": 12
}

CONFIG_SCHEMA = cv.Schema(
  binary_sensor.binary_sensor_schema(Mch2022_rp2040BinarySensor)
  .extend(
      {
        cv.GenerateID(CONF_MCH20222_RP2040): cv.use_id(Mch2022_rp2040Component),
        cv.Required(CONF_INPUT): cv.string,
        # cv.Optional(CONF_BUTTONS[CONF_BUTTON])
      }
  )
  .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(
      config[CONF_ID],
      config[CONF_INPUT]
    )
    paren = await cg.get_variable(config[CONF_MCH20222_RP2040])
    # sens = await binary_sensor.new_binary_sensor(config)
    input_int = CONF_INPUTS[config[CONF_INPUT]]
    # cg.add(paren.set_sub_binary_sensor(input_int, sens))
    await cg.register_component(var, config)
 