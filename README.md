# Zephyr-Application
My personal Zephyr Applications Repo

### Cheat Command lines
- west build -p -b nrf52840dongle_nrf52840 app
- nrfutil pkg generate --hw-version 52 --sd-req=0x00         --application build/zephyr/zephyr.hex         --application-version 1 app.zip
- nrfutil dfu usb-serial -pkg app.zip -p /dev/ttyACM0
