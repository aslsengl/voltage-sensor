#ifndef __LED_APP_H__
#define __LED_APP_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "pico/stdlib.h"

// enum specifying the LED states
typedef enum {
    LED_STATUS,
    LED_ERROR,
    LED_MAX_NUM,
} led_app_leds_e;

// LED Control Struct
typedef struct {
    uint8_t io_num;
    uint32_t last_time_ms;
    uint32_t toogle_interval_ms;
} led_app_led_ctl_t;

// Function prototypes
void led_init(void);

void led_on(led_app_leds_e led);  

void led_off(led_app_leds_e led);

void led_set_toggle(led_app_leds_e led, uint32_t interval_ms);

void led_toggle_task(void);

#ifdef __cplusplus
}
#endif
#endif // __LED_APP_H__
