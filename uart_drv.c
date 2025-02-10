#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "uart_drv.h"

uart_inst_t *UART_NUM_USED = uart1; // Start UART1

uint8_t uart_driver_init(uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity){
    uart_init(UART_NUM_USED, baud_rate);
    uart_set_format(UART_NUM_USED, data_bits, stop_bits, parity);

    // UART1 TX is on GPIO4 RX is on GPIO5
    gpio_set_function(4, GPIO_FUNC_UART); // TX
    gpio_set_function(5, GPIO_FUNC_UART); // RX
    
    return 0;
}

void uart_driver_write(uint8_t *data, uint16_t len){
    for(uint16_t i = 0; i < len; i++){
        while(!uart_is_writable(UART_NUM_USED));
        uart_putc(UART_NUM_USED, data[i]);
    }
}

int uart_driver_read(uint8_t *data, uint16_t len){
    uint16_t bytesRead = 0;
    for(uint16_t i = 0; i < len; i++){
        if(uart_is_readable(UART_NUM_USED)){
        data[i] = uart_getc(UART_NUM_USED);
        bytesRead++;
        } else {
            break;
        }
    }
    return bytesRead;
}
