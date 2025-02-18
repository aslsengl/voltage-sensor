#include "timer_app.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "measurement_app.h"
#include <stdio.h>

static timer_callback_t user_callback = NULL; //User callback function
static repeating_timer_t timer_instance; //Timer instance

// Timer interrupt handler
bool timer_callback(struct repeating_timer *t){
    if(user_callback){
        user_callback(); //Call user callback function
    }

    // Get ADC measurements
    uint16_t raw_value = measurement_app_get_raw_adc();
    float voltage = measurement_app_get_voltage(raw_value);

    return true;
}

// Initialize the timer
void timer_app_start(uint32_t interval_us, timer_callback_t callback){
    user_callback = callback; //Set user callback function
    add_repeating_timer_us(interval_us, timer_callback, NULL, &timer_instance);
}

// Stop the timer
void timer_app_stop(void){
    cancel_repeating_timer(&timer_instance); //Cancel the timer
}
