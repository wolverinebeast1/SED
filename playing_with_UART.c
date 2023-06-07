/*
This code isnt perfect and requires improvment its just a basic usage of the UART ports to print 
thing out via terminal, also it demonstrates the basic knowledge on how to configure timers and 
generate delays
*/
/*
    ____________________________
   /                           /\
   /                         _/ /\
  /          MSP4305529      / \/
 /                           /\
/___________________________/ /
\___________________________\/
 \ \ \ \ \ \ \ \ \ \ \ \ \ \ \

*/

#include <msp430.h>
#include "MSP_Serial.h" //in order to make UART work

void config_timer() {
    TA0CTL |= TASSEL_1 + MC_1 + TACLR; // Set TimerA to ACLK, Up mode, and clear timer
}

void delay_seconds(unsigned int ms) {
        TA0CCR0 = ms*32.768;
        while ((TA0CTL & TAIFG) == 0); // Wait for TimerA interrupt flag to be set
        TA0CTL &= ~TAIFG; // Clear the TimerA interrupt flag
    }
int calc_times(int seconds ,  int ms) {
    seconds = seconds*1000; //converting ms into seconds
    int times = seconds/ms; //times that the loop will do this delay 
    return times; 
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    ConfigUART(); //mandatory to make UART work
    config_timer(); 
    unsigned int i = 0;
    char buffer[100]; //variable that will store all the "i" variables
    unsigned int times = calc_times(10, 80); //calculates how many times the loop needs to do an certain ms delay 
    volatile unsigned int retardo = 0;
    while (1) {
        i++; // Increment the variable i

        sprintf(buffer, "%d\n\r", i); // Convert i to string format
        uart_puts(buffer); // Print the string via UART
        for(retardo = 0 ; retardo < times ; retardo++) {
        delay_seconds(80); // Delay
        }
    }

    return 0;
}
