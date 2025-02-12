#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "adc_drv.h"

adc_status_t adc_driver_init(const adc_config_t *config){
    if (config == NULL){
        return ADC_ERROR_INIT;
    }

    adc_init();

    gpio_set_function(config->channel, 0x2);

    adc_select_input(config->channel);

    adc_set_temp_sensor_enabled(false);

    return ADC_SUCCESS;
}

// function to read raw ADC value
adc_status_t adc_driver_read_raw(uint16_t *value){
    if(value == NULL){
        return ADC_ERROR_READ;
    }

    *value = adc_read();

    return ADC_SUCCESS;
}

// Function to read ADC voltage value
adc_status_t adc_driver_read_voltage(float *voltage){
    if(voltage == NULL){
        return ADC_ERROR_READ;
    }
    uint16_t raw_value = 0;
    adc_status_t status = adc_driver_read_raw(&raw_value);
    if (status != ADC_SUCCESS){
        return ADC_ERROR_READ;
    }
    
    // Convert raw ADC value to voltage
    *voltage = ((float)raw_value * 3.3f) / 4095.0f;

    return ADC_SUCCESS;
}
