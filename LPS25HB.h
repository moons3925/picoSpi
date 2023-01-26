#ifndef __LPS25HB_H
#define __LPS25HB_H

#include "hardware/spi.h"
#include "pico/stdlib.h"

#define PICO_DEBUG

#define PIN_MISO 16  // 21pin
#define PIN_CS 17    // 22pin
#define PIN_SCK 18   // 24pin
#define PIN_MOSI 19  // 25pin

#define LPS25HB_ADRS 0x5c
#define WHO_AM_I 0x0f
#define CTRL_REG1 0x20
#define WAKE_UP 0x90
#define P_ADRS 0x28
#define LPS25HB_DEVICE_CODE 0xbd

bool LPS25HB_init(spi_inst_t *, uint8_t *, uint8_t *);
bool LPS25HB_write(spi_inst_t *i2c, uint8_t *, int);
bool LPS25HB_read(spi_inst_t *i2c, uint8_t *, int);

#endif /* __LPS25HB_H */
