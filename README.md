# Rpi_PICO_RP2040_ST7796_Driver_PIO_SPI

pio spi

#define PIN_SCK 2
#define PIN_MOSI 3
#define PIN_MISO 4
#define PIN_CS 5 // 片选由pio程序初始化，由pio程序控制
#define PIN_BKL 6
#define PIN_RST 7
#define PIN_DC 8
#define PIN_TOUCH_CS 14
#define PIN_SD_CS 15

像素格式 RGB666
默认开启了图片颜色增强
添加了fatfs驱动
