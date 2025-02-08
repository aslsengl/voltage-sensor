#include <stdio.h>
#include "pico/stdlib.h"
#include "led_app.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);

    led_init();     // Initialize the LED

    while (1) {
        printf("Hello from Pico2\r\n");

        led_toggle(LED_STATUS);     // Toggle the status LED
        sleep_ms(1000);
    }
    return 0;
}
