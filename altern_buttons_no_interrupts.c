
//Alternar botones , Código SIN INTERRUPCIONES

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



//En este caso se quito el jumper y se uso el PIN P1.4 para encender el LED rojo
void Config_ports() {

    P2DIR |= BIT1; //Config button 1
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR |= BIT1; //Config button 2
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P1DIR |= BIT4; //Red LED
    P1OUT &= ~BIT4;
    P4DIR |= BIT7; //Green LED
    P4OUT &= ~BIT7;
    return;
}




int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    ConfigUART(); //must have to make UART work
    Config_ports(); //llamamos la funcion configurar puertos

while(1){
    if((P2IN & BIT1) == 0) { //Si boton pulsado , detecta un 0

        P1OUT |= BIT4; //LED rojo on
        P4OUT &= ~BIT7; //LED verde off

        uart_puts("Boton 1 pulsado, LED rojo encendido\n\r");
    }
    if((P1IN & BIT1) == 0) { //Si boton 2 pulsaod , detecta un 0

        P1OUT &= ~BIT4; //led rojo off
        P4OUT |= BIT7; //led verde on
        uart_puts("Boton 2 pulsado, LED verde encendido\n\r");
    }
}
    return 0;
}
