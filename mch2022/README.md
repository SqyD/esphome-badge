## Esphome has an App on the MCH2022 badge
Very much a work in progress. Based on esp-idf as Arduino support is very limited for this badge. No OTA by design.
#### Working features
* Wifi
* RGB Leds
* I2C
* Bosch bme680 climate sensor
#### Not working (yet?)
* Display insists on a whitescreen of death and generic errors in the log. I've tried many variations of the configuration. Not sure why the [esphome component](https://esphome.io/components/display/ili9xxx) for the ili9341 display doesn't like this setup. Perhaps it's confused by the FPGA that's also on the SPI bus?
* All the I/O connected to the rpi204 chip like Buttons, IR Led, LCD Backlight, etc
* Audio (likely due to limitations in support for this esphome feature with esp-idf)
* The BNO055 accelerometer, gyroscope, magnetometer sensor (no component in esphome for this (yet))

### Building
* Create a new esp32dev device in esphome
* Modify the generated yaml to include the sections from the mch2022-badge.yaml file in this repo.
* Make sure to upload the partitions.csv file to a folder called mch2022-badge next to the yaml
* Install and select the manual upload option
* When done select the "OTA format" version of the binary. This will download the file mch2022-badge.ota.bin.
* Rename it to main.bin and use the mch2022-tools package to upload it to the mch2022 badge you have connected to your machine. Something like ```./mch2022-tools/app_push.py -r esphome/main.bin esphome Esphome 1``` should do the trick.
* This should run the application but you can also see the Esphome app in the Apps section of the BadgeOS launcher. 