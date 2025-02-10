#include "pico/stdlib.h"
#include "hardware/gpio.h"

uint8_t gpio_driver_get(uint8_t io_num)
{
    return gpio_get(io_num);
}

void gpio_driver_set(uint8_t io_num, uint8_t io_val)
{
    gpio_put(io_num, io_val);
}

void gpio_driver_toggle(uint8_t io_num)
{
    gpio_put(io_num, !gpio_get(io_num));
}

int gpio_driver_init(uint8_t io_num, uint8_t io_dir)
{
    gpio_init(io_num);
    gpio_set_dir(io_num, io_dir);
    return 0;
}
