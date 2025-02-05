#include "gpio_driver.h"
#include "pico/stdlib.h"

#define LED_PIN (25)

void led_init(void) {
    gpio_driver_init(LED_PIN, GPIO_OUT);
}

void led_on(void) {
    gpio_driver_set(LED_PIN, 1);
}

void led_off(void) {
    gpio_driver_set(LED_PIN, 0);
}

void led_toggle(void) {
    gpio_driver_toggle(LED_PIN);
}