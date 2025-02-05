#include <stdio.h>
#include "pico/stdlib.h"
#include "gpio_driver.h"

#define PICO_DEBUG_LED_PIN (25)

int main() {
    stdio_init_all();
    gpio_driver_init(PICO_DEBUG_LED_PIN, GPIO_OUT);
    while (1) {
        printf("Hello from Pico2\r\n");
        gpio_driver_toggle(PICO_DEBUG_LED_PIN);
        sleep_ms(1000);
    }
}
