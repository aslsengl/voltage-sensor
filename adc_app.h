#ifndef __ADC_APP_H__
#define __ADC_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "adc_drv.h"

adc_status_t adc_app_init(const adc_config_t *config);

adc_status_t adc_app_read_raw(uint16_t *value);

adc_status_t adc_app_read_voltage(float *voltage);

#ifdef __cplusplus
}
#endif
#endif // __ADC_APP_H__