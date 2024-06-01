cmake_minimum_required(VERSION 3.19)

# Set the C/C++ standard
#set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_NAME "Template")
set(TARGET_NAME "Template")

# Checks if pico sdk and pico extras env. variables are set
if(NOT DEFINED ENV{PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH environment variable is not defined")
endif()
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
set(PICO_EXTRAS_PATH $ENV{PICO_EXTRAS_PATH})

# Board type
set(FAMILY rp2040)
set(PICO_BOARD pico_w CACHE STRING "Board type")
set(BOARD pico_sdk)

# Toolchain and module path vars for windows

set(CMAKE_TOOLCHAIN_FILE ${PICO_SDK_PATH}/cmake/preload/toolchains/pico_arm_gcc.cmake)

if(WIN32)
    set(CMAKE_MODULE_PATH ${PICO_INSTALL_PATH}/)
endif()

# Project name, version and languages
project(${PROJECT_NAME}
    VERSION 1.0 
    LANGUAGES C CXX ASM
)

# initialize pico sdk
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)
pico_sdk_init()

# ensure pico sdk >= 1.3.0 (not necessary)
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Add directories
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable target
add_executable(${TARGET_NAME})

# Add source files
target_sources(${TARGET_NAME} PUBLIC src/main.c)

# Specify target
target_link_libraries(${TARGET_NAME} PUBLIC pico_stdlib hardware_i2c)

# Link stdio to usb serial
pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 1)

# Generate uf2 file for flashing
pico_add_extra_outputs(${TARGET_NAME})
