#ifndef __FILTER_APP_H__
#define __FILTER_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

void filter_app_init(float initial_value);

float filter_app_apply(float new_value);

#ifdef __cplusplus
}
#endif

#endif // __FILTER_APP_H__