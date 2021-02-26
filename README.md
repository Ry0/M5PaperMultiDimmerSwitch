# M5PaperMutiDimmerSwitch

![img](.image/homekit-badge.png)

Multiple programmable switches for HomeKit using M5Paper.
 
# DEMO
 
comming soon.
 
# Features

* Currently, 8 buttons can be defined.
* M5Paper alone can work as a HomeKit accessory. (No need for Homebridge, etc.)
* The button design can be changed by the simple UI drawing class.
* Supports single tap only. Double tap and long press are not supported.
 
# Requirement

* M5Paper (Web site: https://m5stack.com/products/m5paper-esp32-development-kit-960x540-4-7-eink-display-235-ppi)
* Arduino IDE
* ESPHap (fork url: https://github.com/Ry0/ESPHap)
 
# Installation

In the official repository, only up to six buttons could be added, so I forked and changed the value of `#define`. If you want to build with the latest version, just change the relevant part in the official repository.

https://github.com/Ry0/ESPHap/commit/5b92855fc55a41edb37e49e51e06f6f79bd9f06a

```bash
cd ~/Documents/Arduino/libraries/
git clone https://github.com/Ry0/ESPHap.git
unrar x ESPHap/wolfssl/wolfSSL.rar

cd <your workspace>
git clone https://github.com/Ry0/M5PaperMutiDimmerSwitch.git
cd M5PaperMutiDimmerSwitch/M5PaperMutiDimmerSwitch
```

Change your Wifi SSID and password(`wifi_info.h`).

```cpp
#ifndef _WIFI_INFO_H_
#define _WIFI_INFO_H_

const char *ssid = "ssid";
const char *password = "password";

#endif
```

Build it with the Arduino IDE.
 
# Usage
 
comming soon...
 
# Note
 
If you want to change the image of the button, use the following.  
https://github.com/m5stack/M5EPD/tree/main/tools/image2gray

If you want to change the font, use the following.  
https://github.com/m5stack/M5EPD/tree/main/tools/ttf2bin
 
# License
 
M5PaperMutiDimmerSwitch is under [MIT license](./LICENSE)