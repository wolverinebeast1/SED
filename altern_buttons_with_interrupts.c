//Alternar botones , Código CON INTERRUPCIONES

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

#include "MSP_Serial.h"

void config_LEDS() {
  P1DIR |= BIT0;
  P4DIR |= BIT7;
  P1OUT &= ~BIT0;
  P4OUT &= ~BIT7;

  return;
}

void config_Button_1() {
  P2DIR |= BIT1;
  P2REN |= BIT1;
  P2OUT |= BIT1;

  return;

}
void config_Button_2() {
  P1DIR |= BIT1;
  P1REN |= BIT1;
  P1OUT |= BIT1;

  return;
}

void EI_port1() {

  //Configurar interrup. Boton 1
  P1IES |= BIT1;
  P1IFG &= ~BIT1;
  P1IE |= BIT1;

  return;
}

void EI_port2() {

  //Configurar interrup. Boton 2
  P2IES |= BIT1;
  P2IFG &= ~BIT1;
  P2IE |= BIT1;

  return;

}

//main
int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
  ConfigUART(); //Enable UART
  config_LEDS(); //Configure leds
  config_Button_1(); //configure button 1
  config_Button_2(); //configure button 2
  EI_port1(); //enable interrupts in port 1
  EI_port2(); //enable interrupts in port 2

  __bis_SR_register(GIE + LPM0_bits); //Low powered mode 0 - CPU off

  return 0;
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2(void) {
  uart_puts("You re triggered the interruption\n\r");
  P1OUT |= BIT0; //turn on red led
  P4OUT &= ~BIT7; //turn off green led
  P2IFG &= ~BIT1; //clean the flag
  __bic_SR_register_on_exit(LPM0_bits); // Wake up from low-power mode

}

#pragma vector = PORT1_VECTOR
__interrupt void Port1(void) {
  uart_puts("You ve triggered the interruption\n\r");
  P1OUT &= ~BIT0; //turn off red led
  P4OUT |= BIT7; //turn on green led
  P1IFG &= ~BIT1; //clean the flag
  __bic_SR_register_on_exit(LPM0_bits); // Wake up from low-power mode

}
