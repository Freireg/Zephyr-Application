
# Zephyr Measuring Device


## Overview

This example merge some of the Zephyr Projetc features:
  - Display   (SSD1306 OLED)
  - Sensor    (MPU6050)
  - Shell commands  (not implemented yet)
  - Wifi (not implemented yet)


## Requirements

1. ESP32 Devkit C
2. Zephyr OS and West installed
3. SSD1306 I2C based OLED display 128x64
4. MPU6050 I2C based accelerometer and giroscope

## Wiring and connections

PERIPHERALS --   ESP32  
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

