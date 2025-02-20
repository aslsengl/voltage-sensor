#include <math.h>

#include "filter_app.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "measurement_app.h"
#include "adc_drv.h"

#define WEIGHT_NEW 0.01f // Weight of the new value
#define WEIGHT_OLD (1.0f - WEIGHT_NEW) // Weight of the old value

static float filtered_value = 0.0f; // First value

void filter_app_init(float initial_value){
    filtered_value = initial_value;
}

float filter_app_apply(float new_value){
    if (!new_value) {
        return filtered_value;
    }
    if (fabs(new_value - filtered_value)  / fabs(new_value) > WEIGHT_NEW) {
        filtered_value = new_value;
        printf("Filter threshold exceed %f\n", filtered_value);
        return filtered_value;
    }
    filtered_value = (WEIGHT_NEW * new_value) + (WEIGHT_OLD * filtered_value);

    if(filtered_value < 0){
        filtered_value = 0.0f;
    }
    return filtered_value;
}
