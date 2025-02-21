#ifndef __FILTER_APP_H__
#define __FILTER_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

//Filter type
typedef enum {
    FILTER_NONE,
    FILTER_WEIGHTED,
    FILTER_AVERAGE
} filter_type_t;

void filter_app_init(float initial_value);

void filter_app_set_type(filter_type_t type);

float filter_app_apply(float new_value);

float filter_app_apply_average(float new_value);

#ifdef __cplusplus
}
#endif

#endif // __FILTER_APP_H__
