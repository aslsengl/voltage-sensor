#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "led_app.h"
#include "uart_drv.h"
#include "uart_app.h"
#include "adc_app.h"
#include "measurement_app.h"
#include "timer_app.h"
#include "filter_app.h"

// Initialize the timer
void my_timer_callback(void){
    printf("Timer Interrupt Triggered!\n");

  uint16_t raw_value = measurement_app_get_raw_adc();
  float unfiltered_voltage = ((float)raw_value * (ADC_VREF / ADC_MAX_VALUE)) * ((DEFAULT_R1 + DEFAULT_R2) / DEFAULT_R2);
  float filtered_voltage = measurement_app_get_voltage(raw_value);
  //float voltage = measurement_app_get_voltage(raw_value);
  
  if(raw_value != (uint16_t)-1){
      printf("Periodic ADC Raw Value: %d\n", raw_value);
  } 
  
  /*if(voltage != -1){
      printf("Filtered Periodic ADC Voltage: %.4f\n", voltage);
  }*/
    printf("Unfiltered Periodic ADC Voltage: %.4f\n", unfiltered_voltage);
    printf("Filtered Periodic ADC Voltage: %.4f\n", filtered_voltage);
}

int main() {
    stdio_init_all();
    sleep_ms(2000);

    // Initialize the LED
    led_init();               

    // Initialize the timer
    timer_app_start(TIMER_INTERVAL_US, my_timer_callback);

    uart_app_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0
    }; 

    if(uart_app_init(&uart_config) == UART_SUCCESS){
        printf("UART Initialized\n");
    } else {
        printf("UART Initialization failed\n");
        return -1;
    }

    measurement_app_init();
    measurement_app_set_resistors(DEFAULT_R1, DEFAULT_R2);

    uint8_t data[] = "Hello from Pico2\r\n";
    uart_app_write(data, strlen((char *)data));

    uint8_t rx_buffer[100]  = {0};

    while (1) {

        uart_app_write(data, sizeof(data));  // Send data to UART

        int bytesRead = uart_app_read(rx_buffer, sizeof(rx_buffer));  // Read data from UART

        if (bytesRead > 0){
            printf("UART Received: %s\n", rx_buffer);
        }

        led_toggle(LED_STATUS);     // Toggle the status LED
        sleep_ms(500);
    }
    return 0;
}
