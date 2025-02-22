#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "adc_drv.h"
#include "filter_app.h"
#include "measurement_app.h"

#define WEIGHT_NEW                  (0.01f)             // Weight of the new value
#define WEIGHT_OLD                  (1.0f - WEIGHT_NEW) // Weight of the old value
#define AVERAGE_SAMPLE_COUNT        (20)                // Number of samples to average

static float s_filtered_value           = 0.0f;             // First value
static filter_type_t s_current_filter   = FILTER_AVERAGE;   // Default filter

typedef struct
{
    float sum;
    float sample_buffer[AVERAGE_SAMPLE_COUNT];
    uint8_t sample_index;
    uint8_t sample_filled;
} average_filter_t;

static average_filter_t s_average_filter = {
    .sum = 0.0f,
    .sample_buffer = {0.0f},
    .sample_index = 0,
    .sample_filled = 0
};

// Weighted filter
float filter_app_apply_weighted(float new_value){
    if (!new_value) {
        return s_filtered_value;
    }
    if (fabs(new_value - s_filtered_value)  / fabs(new_value) > WEIGHT_NEW) { // mrc: >> zero division error?
        s_filtered_value = new_value;
        printf("Filter threshold exceed %f\n", s_filtered_value);
        return s_filtered_value;
    }
    s_filtered_value = (WEIGHT_NEW * new_value) + (WEIGHT_OLD * s_filtered_value);

    if(s_filtered_value < 0){
        s_filtered_value = 0.0f;
    }
    return s_filtered_value;
}

// Average filter
float filter_app_apply_average(float new_value) {
    // Subtract the oldest value from sum before overwriting
    s_average_filter.sum -= s_average_filter.sample_buffer[s_average_filter.sample_index];
    
    // Store new value in buffer
    s_average_filter.sample_buffer[s_average_filter.sample_index] = new_value;
    
    // Add new value to sum
    s_average_filter.sum += new_value;
    
    // Move index forward in circular buffer
    s_average_filter.sample_index = (s_average_filter.sample_index + 1) % AVERAGE_SAMPLE_COUNT;
    
    // Ensure sample_filled doesn't exceed buffer size
    if (s_average_filter.sample_filled < AVERAGE_SAMPLE_COUNT) {
        s_average_filter.sample_filled++;
    }
    
    return s_average_filter.sum / s_average_filter.sample_filled;
}

// Apply the filter
float filter_app_apply(float new_value){ // mrc: >> what if user wants both filters?
    switch(s_current_filter){
        case FILTER_WEIGHTED:
            return filter_app_apply_weighted(new_value);
        case FILTER_AVERAGE:
            return filter_app_apply_average(new_value);
        case FILTER_NONE: // mrc: >> more complex filters must be  added here
        default:
            return new_value;
    }
}

void filter_app_init(filter_type_t type)
{
    s_current_filter = type;
    //s_filtered_value = initial_value;
    if (type == FILTER_AVERAGE) {
        for (int i = 0; i < AVERAGE_SAMPLE_COUNT; i++)
        {
            s_average_filter.sample_buffer[i] = 0x00;
        }
        s_average_filter.sample_index = 0;
        s_average_filter.sample_filled = 0;
    }
}
