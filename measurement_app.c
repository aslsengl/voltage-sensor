#include <stdio.h>
#include "adc_drv.h"
#include "adc_app.h"
#include "filter_app.h"
#include "timer_app.h"
#include "measurement_app.h"

#define MEASUREMENT_READ_INTERVAL_MS (1)
#define MEASUREMENT_COMM_INTERVAL_MS (500)

static float R1 = DEFAULT_R1;
static float R2 = DEFAULT_R2; 

typedef struct
{
    float voltage;
} measurement_t;

static measurement_t s_filtered_measurement_result = {
    .voltage = 0.0f
};

static void measurement_app_set_resistors(float r1, float r2){
    if (r1 > 0 && r2 > 0){
        R1 = r1;
        R2 = r2;
    }
}

static float measurement_app_get_raw_adc(void){
    uint16_t raw_value = 0;
    if (adc_app_read_raw(&raw_value) == ADC_SUCCESS){
        return raw_value;
    } else {
        return -1;
    }
}

static float measurement_app_get_voltage(uint16_t raw_value){
    
    if (raw_value > ADC_MAX_VALUE) {
        raw_value = ADC_MAX_VALUE;
    }

    float voltage = ((float)raw_value * (ADC_VREF / ADC_MAX_VALUE));

    float input_voltage = voltage * ((R1 + R2) / R2);

    float filtered_voltage = filter_app_apply(input_voltage);

    if(filtered_voltage < ADC_VREF) filtered_voltage = ADC_VREF;
    if(filtered_voltage < 0) filtered_voltage = 0.0f;

    return filtered_voltage;
}

void measurement_app_reader_task(void)
{
    static uint32_t last_read_time = 0;
    uint32_t current_time = timer_get_sys_time_ms();
    if (current_time - last_read_time >= MEASUREMENT_READ_INTERVAL_MS){
        last_read_time = current_time;
        //printf("%s occured!\n", __func__);
        
        uint16_t raw_value = measurement_app_get_raw_adc();
        float unfiltered_voltage = ((float)raw_value * (ADC_VREF / ADC_MAX_VALUE)) * ((DEFAULT_R1 + DEFAULT_R2) / DEFAULT_R2);
        float filtered_voltage = measurement_app_get_voltage(raw_value);

        //printf("Unfiltered Periodic ADC Voltage: %.4f\n", unfiltered_voltage);
        //printf("Filtered Periodic ADC Voltage: %.4f\n", filtered_voltage);
        s_filtered_measurement_result.voltage = filtered_voltage;
    }
}

void measurement_app_comm_task(void)
{
    static uint32_t last_comm_time = 0;
    uint32_t current_time = timer_get_sys_time_ms();
    if (current_time - last_comm_time >= MEASUREMENT_COMM_INTERVAL_MS){
        last_comm_time = current_time;
        printf("%s occured!\n", __func__);
        printf("Filtered Periodic ADC Voltage: %.4f\n", s_filtered_measurement_result.voltage);
    }
}

void measurement_app_init(void){
    measurement_app_set_resistors(DEFAULT_R1, DEFAULT_R2);
    adc_app_init();
    filter_app_init(FILTER_ENABLE_WEIGHTED | FILTER_ENABLE_AVERAGE);
    //filter_app_init(FILTER_ENABLE_AVERAGE);
    //filter_app_init(FILTER_ENABLE_WEIGHTED);
    //filter_app_init(FILTER_ENABLE_NONE);
}
