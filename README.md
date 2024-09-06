# Esphome on conference badges
This is collection of attempts to get ESPHome firmware running on Badgeteam badges. This repository is very much a work in progress. Note that some of these attempts ceased their activity a long time ago and may never progress as most badgeteam members are actively workin on the next hardware and software for an upcoming badge project. So there is no formal commitment or support but we'll accept your contributions.

<br><br>
Right now you can track progress on these badges:

##SHA2017
All work for gettin esphome on the original sha2017 badge was done by [Nizzle](https://github.com/Nizzle) [here](https://gist.github.com/Nizzle/6971c2cc066e6412740487bcc3b2c62a/). Some minor updates, fixes and simplifications by [SqyD](https://github.com/SqyD). 

##MCH2022

## Hackerhotel2024

## Hints
As there are many ways to use [esphome](https://esphome.io/). What works for your setup will likely vary a lot but here are some tips:
### Secrets
Make sure not to use any of the very insecure placeholders for secrets in these configurations. Use a separate [secrets.yaml file](https://esphome.io/guides/faq.html#1) to store your wifi credentials and regenerate all keys and passwords in the ota, api and wifi sections at the start of the file. One easy way to do this is to just have the esphome dashboard generate new file with just all basics and then past the badge specific sections after these initial sections.
### Additional files
Some of these badges may require additional files besides the initial yaml file. A common one is the partitions.csv file. Make sure you upload it to a subdirectory where you place your yaml file for the firmware compilation.
### All the new things
All badgeteam badges ever released used the latest and greatest components in both hardware and software. This means more mature software platforms such as [platform.io](https://platform.io) which is the foundations for esphome may need some time to keep up. badges released a few years ago may work just fine, while the cutting edge could be a while from ever being of any use as an esphome device. At the time of writing Espressif, the makers of the awesome esp32 chips found in many badge team badges, is transitioning to using more risc-v based chips. To use these more recent versions of the esp-idf framework may be required but these are only supported for a subset of the esphome features available on other frameworks supported by esphome such as Arduino. Similarly esphome and the wider home assistant ecosystem is rapidly evolving. So, there's about all our excuses why this repo is full of abandonded and partial art. Did we mention we welcome contributions?
