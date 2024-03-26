
add_library(ST7796Driver driver.cpp pio_spi.cpp)
target_link_libraries(ST7796Driver
pico_stdlib
hardware_pio
)
pico_generate_pio_header(ST7796Driver ${CMAKE_CURRENT_LIST_DIR}/spi.pio)