#ifndef __LED_APP_H__
#define __LED_APP_H__

#ifdef __cplusplus
extern "C" {
#endif // __LED_APP_H__

#include "pico/stdlib.h"

void led_init(void);

void led_on(void);  

void led_off(void);

void led_toggle(void);

#ifdef __cplusplus
}
#endif
#endif
