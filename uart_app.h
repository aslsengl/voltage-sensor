#ifndef __UART_APP_H__
#define __UART_APP_H__

#ifdef __cplusplus
extern "C" { 
#endif

#include "pico/stdlib.h"

typedef enum{
    UART_SUCCESS = 0,
    UART_ERROR_TIMEOUT = -1,
    UART_ERROR_OVERFLOW = -2,
    UART_ERROR_FRAME = -3,
    UART_ERROR_PARITY = -4,
    UART_ERROR_UNKNOWN = -10
} uart_status;

typedef struct {
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t parity;
} uart_app_config_t;

// Function prototypes
uart_status uart_app_init(const uart_app_config_t *config); // Using struct for UART configuration

uart_status uart_app_write(uint8_t *data, uint16_t len);

uart_status uart_app_read(uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif // __UART_APP_H__