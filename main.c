#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "led_app.h"
#include "uart_drv.h"
#include "adc_app.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);

    led_init();                         // Initialize the LED
    uart_driver_init(115200, 8, 1, 0);  // Inıtialize the UART
    adc_config_t adc_config = {
        .channel = 0,
        .vref = 3.3f,
    };

    if (adc_app_init(&adc_config) == ADC_SUCCESS){
        printf("ADC Initialized\n");
    } else {
        printf("ADC Initialization failed\n");
        return -1;
    }

    uint16_t raw_value = 0;
    float voltage;

    uint8_t data[] = "Hello from Pico2\r\n";
    uart_driver_write(data, strlen((char *)data));

    uint8_t rx_buffer[100]  = {0};

    while (1) {

        // Read raw value
        if (adc_app_read_raw(&raw_value) == ADC_SUCCESS){
            printf("Raw ADC Value: %d\n", raw_value);
        } else {
            printf("Failed to read raw ADC value\n");
        }

        // Read voltage
        if(adc_app_read_voltage(&voltage) == ADC_SUCCESS){
            printf("ADC Voltage: %.2f\n", voltage);
        } else {
            printf("Failed to read ADC voltage\n");
        }

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