#include "led_app.h"
#include "gpio_driver.h"
#include "pico/stdlib.h"

#define LED_PIN (25)
#define LED_ERROR_PIN (26)

static led_app_led_ctl_t led_app_leds[LED_MAX_NUM] = {
    {LED_PIN},          // LED_STATUS
    {LED_ERROR_PIN},    // LED_ERROR
};

void led_init(void) {
    for(int i = 0; i < LED_MAX_NUM; i++) {
        gpio_driver_init(led_app_leds[i].io_num, GPIO_OUT);
    }
}

void led_on(led_app_leds_e led) {
    if (led < LED_MAX_NUM){
        gpio_driver_set(led_app_leds[led].io_num, 1);
    }    
}

void led_off(led_app_leds_e led) {
    if (led < LED_MAX_NUM){
        gpio_driver_set(led_app_leds[led].io_num, 0);
    }    
}

void led_toggle(led_app_leds_e led) {
    if (led < LED_MAX_NUM){
        gpio_driver_toggle(led_app_leds[led].io_num);
    }
}