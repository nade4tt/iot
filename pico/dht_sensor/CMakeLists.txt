cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(dht_sensor  C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generates compile_commands.json (for neovim lsp)

pico_sdk_init()

add_executable(dht_sensor dht_sensor.c)

# Enable USB CDC serial output and disable UART (optional)
pico_enable_stdio_usb(dht_sensor  1)
pico_enable_stdio_uart(dht_sensor  0)

# Link standard hardware libraries
target_link_libraries(dht_sensor  pico_stdlib)

# Create .uf2, .hex, and .bin build targets
pico_add_extra_outputs(dht_sensor )
