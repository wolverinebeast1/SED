/*
This code simulates a traffic light system we all know:D
First of all the red led will light up for 10 seconds , after that 
the red led will turn off and the yellow led will light up for 5 seconds
and finally the yellow led will turn off and the green will light up for 
10 seconds.
Its good to clarify that the yellow LED isnt integrated in the msp4305529 so
in this example I used an external LED connected in series with an 100 ohm resistor
and all that MUST BE CONNECTED to the pin P1.4 in order to make the things work

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
void config_ports() {
    //Select which Pin will generate PWM signal
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

void Config_LEDs() {
    //Red internal LED
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    //Green Internal LED
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    return;
}

void config_timer_PWM() {
    TA0CTL = TASSEL_1 + MC_1 + TACLR; //ACLK + Up mode
    TA0CCTL3 = OUTMOD_7;
    TA0CCR0 = 250;
    TA0CCR3 = 0; //0 means duty cycle = 0% which makes the LED turn off

    return;
}



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    config_ports();
    config_timer_PWM();
    Config_LEDs();


    //Traffic light control
    while (1) {


        P1OUT |= BIT0; // Red for 10 sec
        __delay_cycles(10000000);
        TA0CCR3 = 100; //Orange in this case yellow
        P1OUT &= ~BIT0; //turn off red LED
        __delay_cycles(5000000);
        TA0CCR3 = 0; //yellow LED off
        P4OUT |= BIT7; //Green for 10 sec
        __delay_cycles(10000000);
        P4OUT &= ~BIT7; //Turn off green LED

    }

    return 0;
}


