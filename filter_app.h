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

#define FILTER_ENABLE_NONE       (1 << FILTER_NONE)
#define FILTER_ENABLE_WEIGHTED   (1 << FILTER_WEIGHTED)
#define FILTER_ENABLE_AVERAGE    (1 << FILTER_AVERAGE)

typedef uint8_t filter_enable_t;

void filter_app_init(filter_enable_t type);

float filter_app_apply(float new_value);

float filter_app_apply_average(float new_value);

#ifdef __cplusplus
}
#endif

#endif // __FILTER_APP_H__
