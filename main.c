#include <stdio.h>
#include "pico/stdlib.h"
#include "led_app.h"
#include "uart_drv.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);

    led_init();                         // Initialize the LED
    uart_driver_init(115200, 8, 1, 0);  // Inıtialize the UART

    uint8_t data[] = "Hello from Pico2\r\n";
    uart_driver_write(data, sizeof(data));

    uint8_t rx_buffer[100]  = {0};

    while (1) {
        uart_driver_write(data, sizeof(data));  // Send data to UART

        int bytesRead = uart_driver_read(rx_buffer, sizeof(rx_buffer));  // Read data from UART

        if (bytesRead > 0){
            printf("UART Received: %s\n", rx_buffer);
        }

        led_toggle(LED_STATUS);     // Toggle the status LED
        sleep_ms(500);
    }
    return 0;
}