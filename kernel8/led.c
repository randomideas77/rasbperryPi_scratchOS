// led.c led controll file v0.0.1
#include "main.h"

void delay(unsigned int ms) {
    for (volatile unsigned int i = 0; i < ms * 1000; i++);
}


void led_on(unsigned int duration_ms, unsigned int final_ms) {
    *GPSET0 = (1 << 29);    // turn ACT LED on
    delay(duration_ms);     // pause for duration_ms
    *GPCLR0 = (1 << 29);    // turn ACT LED off
    delay(final_ms);        // inter-flash pause
}

void led_flash_binary(unsigned int value, unsigned int size) {
    for (int i = size; i >= 0; i--) {
        if ((value >> i) & 0x1) {
            led_on(600, 200);  // binary 1
        } else {
            led_on(200, 600);  // binary 0
        }
    }
    delay(1000); // Pause after full binary output
}