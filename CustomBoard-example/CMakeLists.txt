cmake_minimum_required(VERSION 3.20.0)

#list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
#set(BOARD saalro-evk)


find_package(Zephyr)
project(CustomBoard)

target_sources(app PRIVATE src/main.c)
