#include "pico/stdlib.h"
#include "gpio_driver.h"
#include "timer_app.h"
#include "led_app.h"

#define LED_MANAGER_CTRL_INTERVAL_MS (1)
#define LED_PIN (25)
#define LED_ERROR_PIN (26)

static led_app_led_ctl_t led_app_leds[LED_MAX_NUM] = {
    {LED_PIN, 0, 0},          // LED_STATUS
    {LED_ERROR_PIN, 0, 0},    // LED_ERROR
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

void led_set_toggle(led_app_leds_e led, uint32_t interval_ms) 
{
    if (led < LED_MAX_NUM){
        if (interval_ms == 0){
            led_off(led);
        } else if (led_app_leds[led].toogle_interval_ms != interval_ms){
            led_app_leds[led].toogle_interval_ms = interval_ms;
        }
    }
}

void led_toggle_task(void)
{
    static uint32_t last_read_time = 0;
    uint32_t current_time = timer_get_sys_time_ms();
    if (current_time - last_read_time >= LED_MANAGER_CTRL_INTERVAL_MS){
        last_read_time = current_time;
        for (int i = 0; i < LED_MAX_NUM; i++){
            if (led_app_leds[i].toogle_interval_ms > 0){
                if (current_time - led_app_leds[i].last_time_ms >= led_app_leds[i].toogle_interval_ms){
                    gpio_driver_toggle(led_app_leds[i].io_num);
                    led_app_leds[i].last_time_ms = current_time;
                }
            }
        }
    }
}
