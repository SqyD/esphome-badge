import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import binary_sensor
from esphome.const import CONF_ID, DEVICE_CLASS_BATTERY_CHARGING, CONF_INTERRUPT_PIN
from .. import mch2022_rp2040_ns, Mch2022_rp2040Component, CONF_MCH20222_RP2040

DEPENDENCIES = ["mch2022_rp2040"]
CODEOWNERS = ["@SqyD"]

Mch2022_rp2040BinarySensor = mch2022_rp2040_ns.class_(
    "Mch2022_rp2040BinarySensor", binary_sensor.BinarySensor, cg.Component
)

# Buttons
CONF_BUTTON_HOME = "button_home"
CONF_BUTTON_MENU = "button_menu"
CONF_BUTTON_START = "button_start"
CONF_BUTTON_ACCEPT = "button_accept"
CONF_BUTTON_BACK = "button_back"
CONF_BUTTON_SELECT = "button_select"
#Joystick
CONF_JOYSTICK_LEFT = "joystick_left"
CONF_JOYSTICK_PRESS = "joystick_press"
CONF_JOYSTICK_DOWN = "joystick_down"
CONF_JOYSTICK_UP = "joystick_up"
CONF_JOYSTICK_RIGHT = "joystick_right"
CONF_BATTERY_CHARGING = "battery_charging"

# Additional icons
ICON_BUTTON_HOME = "mdi:home"
ICON_BUTTON_MENU = "mdi:menu-open"
ICON_BUTTON_START = "mdi:play"
ICON_BUTTON_ACCEPT = "mdi:keyboard-return"
ICON_BUTTON_BACK = "mdi:backspace"
ICON_BUTTON_SELECT = "mdi:select"

ICON_JOYSTICK_LEFT = "mdi:gamepad-circle-left"
ICON_JOYSTICK_PRESS = "mdi:ggamepad-circle"
ICON_JOYSTICK_DOWN = "mdi:gamepad-circle-down"
ICON_JOYSTICK_UP = "mdi:gamepad-circle-up"
ICON_JOYSTICK_RIGHT = "mdi:gamepad-circle-right"

ICON_BATTERY_CHARGING = "mdi:battery_charging"


SENSORS = {
    CONF_BUTTON_HOME: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_HOME,
    ),
    CONF_BUTTON_MENU: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_MENU,
    ),
    CONF_BUTTON_START: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_START,
    ),
    CONF_BUTTON_ACCEPT: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_ACCEPT,
    ),
    CONF_BUTTON_BACK: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_BACK,
    ),
    CONF_BUTTON_SELECT: binary_sensor.binary_sensor_schema(
        icon=ICON_BUTTON_SELECT,
    ),
    CONF_JOYSTICK_LEFT: binary_sensor.binary_sensor_schema(
        icon=ICON_JOYSTICK_LEFT,
    ),
    CONF_JOYSTICK_PRESS: binary_sensor.binary_sensor_schema(
        icon=ICON_JOYSTICK_PRESS,
    ),
    CONF_JOYSTICK_DOWN: binary_sensor.binary_sensor_schema(
        icon=ICON_JOYSTICK_DOWN,
    ),
    CONF_JOYSTICK_UP: binary_sensor.binary_sensor_schema(
        icon=ICON_JOYSTICK_UP,
    ),
    CONF_JOYSTICK_RIGHT: binary_sensor.binary_sensor_schema(
        icon=ICON_JOYSTICK_RIGHT,
    ),
    CONF_BATTERY_CHARGING: binary_sensor.binary_sensor_schema(
        icon=ICON_BATTERY_CHARGING,
        # device_class=DEVICE_CLASS_BATTERY_CHARGING,
    ),
}

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_MCH20222_RP2040): cv.use_id(Mch2022_rp2040Component),
        cv.Optional(CONF_INTERRUPT_PIN, default="34"): pins.internal_gpio_input_pin_schema,
    }
).extend(
    { cv.Optional(sensor): schema for sensor, schema in SENSORS.items() }
)

#async def to_code(config):
    # paren = await cg.get_variable(config[CONF_MCH20222_RP2040])

#    for sensor_ in SENSORS:
        
        #if conf := config.get(type_):
        #    sens = await binary_sensor.new_binary_sensor(conf)
        #    binary_sensor_type = getattr(BinarySensorTypeEnum, sensor_.upper())
        #    cg.add(paren.set_sub_binary_sensor(binary_sensor_type, sens))

#CONFIG_SCHEMA = cv.All(
#    cv.COMPONENT_SCHEMA.extend(
#        {
#            cv.GenerateID(): cv.declare_id(Mch2022_rp2040BinarySensor),
#            cv.GenerateID(CONF_MCH20222_RP2040): cv.use_id(Mch2022_rp2040Component),
            # cv.Optional(CONF_HAS_TARGET): binary_sensor.binary_sensor_schema(
            #    device_class=DEVICE_CLASS_OCCUPANCY
            #),
#        }
#    ),
#)


#async def to_code(config):
#    var = cg.new_Pvariable(config[CONF_ID])
#    await cg.register_component(var, config)
#    mch2022_rp2040 = await cg.get_variable(config[CONF_MCH20222_RP2040])
#    cg.add(mch2022_rp2040.register_listener(var))