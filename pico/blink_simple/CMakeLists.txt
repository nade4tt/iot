cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(blink_simple  C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generates compile_commands.json (for neovim lsp)

pico_sdk_init()

add_executable(blink_simple blink_simple.c)

# Enable USB CDC serial output and disable UART (optional)
pico_enable_stdio_usb(blink_simple 1)   # Enables serial print output over the USB CDC interface
pico_enable_stdio_uart(blink_simple 0)  # Disables UART hardware pins for stdio output
pico_add_extra_outputs(blink_simple)    # Generates .uf2/.hex/.bin/.map alongside the ELF

# Link standard hardware libraries
target_link_libraries(blink_simple  pico_stdlib)

# Create .uf2, .hex, and .bin build targets
pico_add_extra_outputs(blink_simple )
