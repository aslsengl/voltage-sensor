#ifndef __UART_DRV_H__
#define __UART_DRV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"
#include "hardware/uart.h"

extern uart_inst_t *UART_NUM_USED;

// UART Control Struct
#define UART_BAUD_DEFAULT 115200
#define UART_DATA_BITS_DEFAULT 8
#define UART_STOP_BITS_DEFAULT 1
#define UART_PARITY_DEFAULT 0

uint8_t uart_driver_init(uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);

void uart_driver_write(uint8_t *data, uint16_t len);

int uart_driver_read(uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif // __UART_DRV_H__
