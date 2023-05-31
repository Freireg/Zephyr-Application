
# LCD I2C example in Zephyr


## Overview


This sample shows how to interface an I2C Monochrome OLED display and using LVGL in Zephyr. 
Based on [TrevorHeyl Example]("https://github.com/TrevorHeyl/Zephyr_OLED_SSD1306_LVGL")

## Requirements

1. ESP32 Devkit C
2. Zephyr OS and West installed
3. SSD1306 I2C based OLED display 128x64

## Wiring and connections

DISPLAY    ESP32  
VSS  --  GND  
VDD  --  3V3  
SCL  --  GPIO22  
SDA  --  GPIO21   



## Building and Running
Build and flash as follows:
<br>
For the first build: 

For esp32 board 

$> west build -p -b esp32

To Flash:

$> west flash


After flashing, optinally view the printk output on a terminal emnulator @ 115200, no handshaking

$> west flash ; minicom
