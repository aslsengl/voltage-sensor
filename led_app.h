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
} led_app_led_ctl_t;

// Function prototypes
void led_init(void);

void led_on(led_app_leds_e led);  

void led_off(led_app_leds_e led);

void led_toggle(led_app_leds_e led);

#ifdef __cplusplus
}
#endif
#endif // __LED_APP_H__
