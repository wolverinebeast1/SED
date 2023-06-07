
/*

In this exercise we wrote a simple program that controls the brightness of the external LED located in the protobar
in order to achieve that behaviour we need to generate a PWM signal in a certain pin (in this case its P1.4) , to control
the brightness of the LED we need to adjust the duty cycle which is determined in the TA0CCR3 register and to adjust it we need
to use two buttons , one button for increasing the brightness and another for decreasing the brightness.
This example is done WITHOUT INTERRUPTIONS

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

void config_ports() {
    P1DIR |= BIT4;
    P1SEL |= BIT4;

    // Button 1
    P1DIR &= ~BIT1;  // Set P1.1 as input
    P1REN |= BIT1;  // Enable pull-up resistor
    P1OUT |= BIT1;  // Set pull-up mode

    // Button 2
    P2DIR &= ~BIT1;  // Set P2.1 as input
    P2REN |= BIT1;  // Enable pull-up resistor
    P2OUT |= BIT1;  // Set pull-up mode

    return;
}

//Configuration of the timer
void config_timer() {
    TA0CTL = TASSEL_1 + MC_1 + TACLR; //ACLK + Up mode
    TA0CCTL3 = OUTMOD_7;
    TA0CCR0 = 250;
    TA0CCR3 = 12;

    return;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    config_ports();
    config_timer();

    while (1) {
        if ((P2IN & BIT1) == 0) {
            if (TA0CCR3 > 0) {
                TA0CCR3 -= 12; //duty cycle -5%
            }
            __delay_cycles(100000);  // Delay for debouncing
        }

        if ((P1IN & BIT1) == 0) {
            if (TA0CCR3 < 250) {
                TA0CCR3 += 12; //duty cyle +5%
            }
            __delay_cycles(100000);  // Delay for debouncing
        }
    }

    return 0;
}
