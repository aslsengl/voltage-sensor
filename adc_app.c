#include "adc_app.h"
#include "adc_drv.h"

adc_status_t adc_app_init(){
    adc_config_t adc_config;

    adc_config.channel = 0;
    adc_config.vref = 3.3f;

    if (adc_driver_init(&adc_config) != ADC_SUCCESS){
        return ADC_ERROR_INIT;
    }
    return ADC_SUCCESS;
}

// Function to read raw ADC value
adc_status_t adc_app_read_raw(uint16_t *value){
    if (value == NULL){
        return ADC_ERROR_READ;
    }

    // Read raw ADC value from the driver
    if (adc_driver_read_raw(value) != ADC_SUCCESS){
        return ADC_ERROR_READ;
    }
    return ADC_SUCCESS;
}

// Function to read ADC voltage
adc_status_t adc_app_read_voltage(float *voltage){
    if(voltage == NULL){
        return ADC_ERROR_READ;
    }
    if(adc_driver_read_voltage(voltage) != ADC_SUCCESS){
        return ADC_ERROR_READ;
    }
    return ADC_SUCCESS;
}

