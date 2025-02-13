#include "uart_app.h"
#include "uart_drv.h"

uart_status uart_app_init(const uart_app_config_t *config){
    if (!config){
        return UART_ERROR_UNKNOWN;  // Null control
    }

    if (uart_driver_init(config->baud_rate, config->data_bits, config->stop_bits, config->parity) != 0){
        return UART_ERROR_UNKNOWN;
    }


    return UART_SUCCESS;
} 

uart_status uart_app_write(uint8_t *data, uint16_t len){
    if (UART_NUM_USED == NULL){
        return UART_ERROR_UNKNOWN;  
    }

    uart_driver_write(data, len);
    
    return UART_SUCCESS;
}

uart_status uart_app_read(uint8_t *data, uint16_t len){
    if(!data){
        return UART_ERROR_UNKNOWN;
    }

    int bytesRead = uart_driver_read(data, len);

    if (bytesRead < 0){
        return UART_ERROR_UNKNOWN;
    }

    return UART_SUCCESS; 
}
