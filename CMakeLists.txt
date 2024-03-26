# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/wjl/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(RpDriver7796 C CXX ASM)
include_directories(ST7796DriverPioSpi FatFs_SPI/include FatFs_SPI/sd_driver  touchDriver UartReceiver)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(RpDriver7796 main.cpp )
add_subdirectory(ST7796DriverPioSpi)
add_subdirectory(FatFs_SPI)
add_subdirectory(touchDriver)
add_subdirectory(UartReceiver)

pico_set_program_name(RpDriver7796 "RpDriver7796")
pico_set_program_version(RpDriver7796 "0.1")

pico_enable_stdio_uart(RpDriver7796 1)
pico_enable_stdio_usb(RpDriver7796 0)

# Add the standard library to the build
target_link_libraries(RpDriver7796
        ST7796Driver
        FatFs_SPI
        UartReceiver
        hardware_pio
        hardware_vreg
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(RpDriver7796 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

pico_add_extra_outputs(RpDriver7796)

