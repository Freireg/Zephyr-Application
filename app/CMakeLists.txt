cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32)
find_package(Zephyr)
project(my_application)

target_sources(app PRIVATE src/main.c)
