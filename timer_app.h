#ifndef __TIMER_APP_H__
#define __TIMER_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

#define TIMER_INTERVAL_US       (1000)  // 1 ms

typedef void (*timer_callback_t)(void);

uint32_t timer_get_sys_time_ms(void);

void timer_app_start(uint32_t interval_us, timer_callback_t callback);

void timer_app_stop(void);

#ifdef __cplusplus
}
#endif

#endif // __TIMER_APP_H__
