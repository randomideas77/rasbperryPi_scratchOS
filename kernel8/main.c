// main.c 0.1.2
#include "main.h"       // main header file
#include "mailbox.c"    // mailbox controller file
#include "led.c"        // led controller file

int mathOne(unsigned int num1, unsigned int num2, unsigned int op){
    if (num1 > 0 | num2 > 0 | op > 0){
        if (op == 1 | op <= 3){ return(num1 + num2); } 
        else if((op == 2 | op <= 4) && (num1 > num2)){ return(num1 - num2); }
        else if(op == 3 | op <= 5){ return(num1 * num2); }
        else { return(0); }
    }
}

void ledPatternOne() {
    led_on(800, 150);
    delay(500);
    led_on(500, 50);
    led_on(500, 50);
}

void kernel_main(void) {
    // Set GPIO29 to output
    unsigned int r = *GPFSEL2;
    r &= ~(7 << 27);      // Clear bits 27-29 (GPIO29)
    r |=  (1 << 27);      // Set GPIO29 as output
    *GPFSEL2 = r;


    ledPatternOne();
    delay(1000);

    unsigned int revision = get_revision_number();
    led_flash_binary(revision, 31);
    delay(1000);

    unsigned int armClock = get_clock_speed(3);
    led_flash_binary(armClock, 31);

    int num0 = 0;
    // main loop
    while (1) {
        num0 = num0 + 1;
        //random math stuff to make the cpu do stuff
        int num1 = mathOne(num0, 1, 1); // should return 3
        int num2 = mathOne(4, 3, 2); // should return 1
        int num3 = mathOne(num1, num2, 3); // should return 3
        led_flash_binary(num3, 3);  // flashes 4 bit output of num3
    }
}
