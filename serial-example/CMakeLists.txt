cmake_minimum_required (VERSION 3.22)
set(BOARD nucleo_l476rg)

find_package(Zephyr)
project(serial-example)

target_sources(app PRIVATE src/main.c)