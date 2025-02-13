#ifndef __ADC_DRV_H__
#define __ADC_DRV_H__

#ifdef __cplusplus 
extern "C" {
#endif

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define ADC_VREF 3.3f
#define ADC_MAX_VALUE 4095.0f

typedef enum {
    ADC_SUCCESS = 0,
    ADC_ERROR_INIT = -1,
    ADC_ERROR_READ = -2
} adc_status_t;

typedef struct {
    uint8_t channel;
    float vref;
} adc_config_t;

adc_status_t adc_driver_init(const adc_config_t *config);

adc_status_t adc_driver_read_raw(uint16_t *value);

adc_status_t adc_driver_read_voltage(float *voltage);

#ifdef __cplusplus
}
#endif
#endif // __ADC_DRV_H__

