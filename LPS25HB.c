#include "LPS25HB.h"

#include <stdio.h>  // implicit declaration of function 'puts' への対策

bool LPS25HB_init(spi_inst_t *spi, uint8_t *sbuf, uint8_t *rbuf) {
    bool result;
    sbuf[0] = WHO_AM_I | 0x80;
    sbuf[1] = 0;

    gpio_put(PIN_CS, 0);
    sleep_us(2);
    result = LPS25HB_write(spi, sbuf, 1);
    if (result) {
        sleep_us(2);
        bool result2 = LPS25HB_read(spi, rbuf, 1);
        if (result2) {
            if (LPS25HB_DEVICE_CODE == rbuf[0]) {
                gpio_put(PIN_CS, 1);
                return true;
            } else {
                gpio_put(PIN_CS, 1);
                return false;
            }
        }
    } else {
        gpio_put(PIN_CS, 1);
        return false;
    }
}

bool LPS25HB_write(spi_inst_t *spi, uint8_t *buf, int length) {
    int ret = spi_write_blocking(spi, buf, length);
    if (ret == length) {
#ifdef PICO_DEBUG
        puts("SPI write success.");
#endif
        return true;
    } else {
#ifdef PICO_DEBUG
        if (PICO_ERROR_GENERIC == ret) {
            puts("PICO Error Generic.");
        } else if (PICO_ERROR_TIMEOUT == ret) {
            puts("PICO Error timeout.");
        }
#endif
    }
    return false;
}

bool LPS25HB_read(spi_inst_t *spi, uint8_t *buf, int length) {
    int ret = spi_read_blocking(spi, 0, buf, length);
    if (ret == length) {
#ifdef PICO_DEBUG
        puts("SPI read success.");
#endif
        return true;
    } else {
#ifdef PICO_DEBUG
        if (PICO_ERROR_GENERIC == ret) {
            puts("PICO Error Generic.");
        } else if (PICO_ERROR_TIMEOUT == ret) {
            puts("PICO Error timeout.");
        }
#endif
    }
    return false;
}