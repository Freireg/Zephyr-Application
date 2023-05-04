cmake_minimum_required (VERSION 3.22)
set(BOARD frdm_k64f)

find_package(Zephyr)
project(AppDev-example)

target_sources(app PRIVATE 
  src/main.c
  src/utils.c
  include/utils.h
  )

target_include_directories(app PRIVATE include)

