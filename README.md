# arduino-oled
Arduino / esp8266 code using  an 128x64 0.96" OLED module


starfield.ino - simple animated starfield

![Imgur](https://i.imgur.com/nZtLore.gif)

ssid.ino - list SSIDs and strength

![](http://i.imgur.com/NQnbHyIm.jpg)

ssid-graph.ino - list SSID names and graph of channel numbers / strength

![](http://i.imgur.com/CG06MZBm.jpg)


netscan.ino - connect to wifi, then ping subnet to find live hosts


Esp8266/OLED Module: £7.40 at https://www.banggood.com/Wemos-Lolin-ESP32-OLED-Module-For-Arduino-ESP32-OLED-WiFi-Bluetooth-Dual-ESP-32-ESP-32S-ESP8266-p-1148119.html


More documentation at
 https://github.com/espressif/arduino-esp32
 http://www.espressif.com/en/products/hardware/esp32/resources
 https://github.com/squix78/esp8266-oled-ssd1306/tree/master/examples/SSD1306SimpleDemo
 https://github.com/ThingPulse/esp8266-oled-ssd1306

In Arduino library manager, install "ESP8266 and ESP32 Oled Driver for SSD1306 display"

For board use WEMOS LOLIN32

Ping library: https://github.com/marian-craciunescu/ESP32Ping
