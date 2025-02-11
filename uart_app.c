#include "uart_app.h"
#include "uart_drv.h"

uart_status uart_app_init(const uart_app_config_t *config){
    if (!config){
        return UART_ERROR_UNKNOWN;  // Null control
    }

    uart_init(UART_NUM_USED, config->baud_rate);
    uart_set_format(UART_NUM_USED, config->data_bits, config->stop_bits, config->parity);

    gpio_set_function(4, GPIO_FUNC_UART); // TX
    gpio_set_function(5, GPIO_FUNC_UART); // RX

    return UART_SUCCESS;
} 

uart_status uart_app_write(uint8_t *data, uint16_t len){
    if (UART_NUM_USED == NULL){
        return UART_ERROR_UNKNOWN;  
    }

    for(uint16_t i = 0; i < len; i++){
        while(!uart_is_writable(UART_NUM_USED));
        uart_putc(UART_NUM_USED, data[i]);
    }

    return UART_SUCCESS;
}

uart_status uart_app_read(uint8_t *data, uint16_t len){
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