#ifndef __GPIO_DRIVER_H__
#define __GPIO_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

uint8_t gpio_driver_get(uint8_t io_num);

void gpio_driver_set(uint8_t io_num, uint8_t io_val);

void gpio_driver_toggle(uint8_t io_num);

int gpio_driver_init(uint8_t io_num, uint8_t io_dir);

#ifdef __cplusplus
}
#endif
#endif
