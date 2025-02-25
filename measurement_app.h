#ifndef __MEASUREMENT_APP_H__
#define __MEASUREMENT_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

#define DEFAULT_R1 (100000.0f)      // 100k
#define DEFAULT_R2 (10000.0f)       // 10k

void measurement_app_reader_task(void);
void measurement_app_comm_task(void);
void measurement_app_init(void);

#ifdef __cplusplus
}
#endif

#endif // __MEASUREMENT_APP_H
