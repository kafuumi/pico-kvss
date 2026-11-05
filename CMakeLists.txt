cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

project(pico-kvss C)

set(KVSS_NVS pico-kvss-nvs)
set(KVSS_ZMS pico-kvss-zms)

add_library(${KVSS_NVS} STATIC
        src/kvss/kvss_crc.c
        src/nvs/nvs.c)
target_compile_options(${KVSS_NVS} PRIVATE -Wall -Wextra)
target_include_directories(${KVSS_NVS} PUBLIC "include/")
target_include_directories(${KVSS_NVS} PRIVATE "src/kvss/")

add_library(${KVSS_ZMS} STATIC
        src/zms/zms.c
        src/kvss/kvss_crc.c)
target_compile_options(${KVSS_ZMS} PRIVATE -Wall -Wextra)
target_include_directories(${KVSS_ZMS} PUBLIC "include/")
target_include_directories(${KVSS_ZMS} PRIVATE "src/kvss/")


