#include <stdio.h>
#include "adc_drv.h"
#include "adc_app.h"
#include "filter_app.h"
#include "measurement_app.h"

static float R1 = DEFAULT_R1;
static float R2 = DEFAULT_R2; 

void measurement_app_init(void){
    adc_app_init();
    filter_app_init(FILTER_AVERAGE);
}

void measurement_app_set_resistors(float r1, float r2){
    if (r1 > 0 && r2 > 0){
        R1 = r1;
        R2 = r2;
    }
}

float measurement_app_get_raw_adc(void){
    uint16_t raw_value = 0;
    if (adc_app_read_raw(&raw_value) == ADC_SUCCESS){
        return raw_value;
    } else {
        return -1;
    }
}

float measurement_app_get_voltage(uint16_t raw_value){
    
    if (raw_value < 0) return -1; // mrc: >> raw value is unsigned, so it can not be negative ! 

    float voltage = ((float)raw_value * (ADC_VREF / ADC_MAX_VALUE));

    float input_voltage = voltage * ((R1 + R2) / R2);

    float filtered_voltage = filter_app_apply(input_voltage);

    if(filtered_voltage < ADC_VREF) filtered_voltage = ADC_VREF;
    if(filtered_voltage < 0) filtered_voltage = 0.0f;

    return filtered_voltage;

    //return voltage * ((R1 + R2) / R2);
}
