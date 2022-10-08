# Zephyr-Application

## Overview
My personal Zephyr Applications Repo

## Current Status
- Application: Blinky example using threads
- Board compatibility: **stm32f4_disc**
- Custom board: **VIRGULINO Board**

## Usefull VSCode Extensions

- [nRF Connect for VS Code Extension Pack](https://marketplace.visualstudio.com/items?itemName=nordic-semiconductor.nrf-connect-extension-pack)

## More usefull info
> Cheat Command lines (for building and releasing on nRF 52840 USB Dongle):
```
west build -p -b nrf52840dongle_nrf52840 app

nrfutil pkg generate --hw-version 52 --sd-req=0x00         --application build/zephyr/zephyr.hex         --application-version 1 app.zip

nrfutil dfu usb-serial -pkg app.zip -p /dev/ttyACM0
```