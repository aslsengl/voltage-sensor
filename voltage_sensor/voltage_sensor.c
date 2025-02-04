#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_PIN 26 // ADC0 input on GPIO26
#define CONVERSION_FACTOR (3.0F / (1 << 12)) // Assuming ADC reference voltage is 3.0V

int main()
{
    stdio_init_all();
    printf("ADC measurement - 10kΩ Resistor\n");

    adc_init();                 //Initialize the ADC module
    adc_gpio_init(ADC_PIN);     //Configure GPIO26 for ADC input
    adc_select_input(0);        //Select ADC0 (GPIO26) as input

    while (1)
    {
        uint16_t raw value = adc_read();                    //Read raw ADC value 
        float voltage = raw_value * CONVERSION_FACTOR;      //Convert ADC value to voltage

        printf("ADC Raw Value: %d, Measured Voltage : %.2fV\n", raw_value, voltage);

        sleep_ms(500);      //Wait 500ms before next reading
    }
}