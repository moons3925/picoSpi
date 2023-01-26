#include <stdio.h>

#include "LPS25HB.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments

int main() {
    uint8_t sbuf[20];
    uint8_t rbuf[20];

    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(spi0, 1000 * 1000);

    spi_set_format(spi0, 8, 1, 1, SPI_MSB_FIRST);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    puts("Hello, SPI!");

    bool result = LPS25HB_init(spi0, sbuf, rbuf);

    if (result) {
        puts("LPS25HB initialize success.");
        sbuf[0] = CTRL_REG1;
        sbuf[1] = WAKE_UP;
        gpio_put(PIN_CS, 0);
        sleep_us(2);
        LPS25HB_write(spi0, sbuf, 2);
        sleep_us(2);
        gpio_put(PIN_CS, 1);
        sleep_ms(10);
        sbuf[0] = P_ADRS | 0xc0;
        gpio_put(PIN_CS, 0);
        sleep_us(2);
        LPS25HB_write(spi0, sbuf, 1);
        sleep_us(2);
        LPS25HB_read(spi0, rbuf, 3);
        gpio_put(PIN_CS, 1);

        int pressure = rbuf[2] << 16 | rbuf[1] << 8 | rbuf[0];
        pressure /= 4096;
        printf("Today's atmospheric pressure is %d[hPa].", pressure);
    } else {
        puts("LPS23HB Init failure.");
    }
    return 0;
}
