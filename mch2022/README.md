## Esphome has an App on the MCH2022 badge
Very much a work in progress. Based on esp-idf as Arduino support is very limited for this badge. No OTA by design.
#### Working features
* Wifi
* RGB Leds in the kite
* I2C
* Bosch bme680 climate sensor
* Display
#### Not working (yet?)
* All the I/O connected to the rpi204 chip like Buttons, IR Led, LCD Backlight, etc
* Audio (likely due to limitations in support for this esphome feature with esp-idf)
* The BNO055 accelerometer, gyroscope, magnetometer sensor (no component in esphome for this (yet))
* FPGA connected i/o: RGB Led, pmod pins.

### Building
* Create a new esp32dev device in esphome
* Modify the generated yaml to include the sections from the mch2022-badge.yaml file in this repo.
* Make sure to upload the partitions.csv file to a folder called mch2022-badge next to the yaml
* Install and select the manual upload option
* When done select the "OTA format" version of the binary. This will download the file mch2022-badge.ota.bin.
* Rename it to main.bin and use the mch2022-tools package to upload it to the mch2022 badge you have connected to your machine. Something like ```./mch2022-tools/app_push.py -r esphome/main.bin esphome Esphome 1``` should do the trick.
* This should run the application but you can also see the Esphome app in the Apps section of the BadgeOS launcher. 