cmake_minimum_required (VERSION 3.22)
set(BOARD frdm_k64f)

find_package(Zephyr)
project(serial-example)

target_sources(app PRIVATE src/main.c)