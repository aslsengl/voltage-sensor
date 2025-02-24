# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(voltage_sensor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(voltage_sensor 
    main.c 
    gpio_driver.c
    led_app.c   #LED Application file added 
    uart_drv.c  #UART driver file added
    uart_app.c  #UART Application file added
    adc_drv.c   #ADC driver file added
    adc_app.c   #ADC Application file added
    measurement_app.c #Measurement Application file added
    timer_app.c #Timer Application file added
    filter_app.c #Filter Application file added
    )

pico_set_program_name(voltage_sensor "voltage_sensor")
pico_set_program_version(voltage_sensor "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(voltage_sensor 0)
pico_enable_stdio_usb(voltage_sensor 1)

# Add the standard library to the build
target_link_libraries(voltage_sensor
        pico_stdlib
        hardware_gpio
        hardware_uart 
        hardware_adc
)

# Add the standard include files to the build
target_include_directories(voltage_sensor PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(voltage_sensor 
        hardware_spi
        hardware_i2c
        )

pico_add_extra_outputs(voltage_sensor)
