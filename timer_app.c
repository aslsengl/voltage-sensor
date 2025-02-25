#include <stdio.h>
#include "timer_app.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "measurement_app.h"

static timer_callback_t     s_user_callback = NULL; //User callback function
static repeating_timer_t    s_timer_instance; //Timer instance

static uint32_t s_sys_time_ms = 0; //System time in microseconds

// Timer interrupt handler
bool timer_callback(struct repeating_timer *t){
    s_sys_time_ms++;
    if(s_user_callback){
        s_user_callback(); //Call user callback function
    }
    return true;
}

uint32_t timer_get_sys_time_ms(void)
{
    return s_sys_time_ms / (TIMER_INTERVAL_US / 1000);
}

// Initialize the timer
void timer_app_start(uint32_t interval_us, timer_callback_t callback){
    s_user_callback = callback; //Set user callback function
    add_repeating_timer_us(interval_us, timer_callback, NULL, &s_timer_instance);
}

// Stop the timer
void timer_app_stop(void){
    cancel_repeating_timer(&s_timer_instance); //Cancel the timer
}
