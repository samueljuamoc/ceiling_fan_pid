#include "config.h"
uint16_t contador;

void TMR0_init(void){
    T0CONbits.TMR0ON = 0;   // Timer0 On/Off Control bit
    T0CONbits.T08BIT = 0;   // Timer0 is configured as a 16-bit counter
    T0CONbits.T0CS = 1;     // Transition on T0CKI pin (RA4) counter
    T0CONbits.T0SE = 0;     // Increment on low-to-high transition on T0CKI pin 
    T0CONbits.PSA = 1;      // TImer0 prescaler is NOT assigned.
    //T0CONbits.T0PS = 0b000; // 1:2 prescale value
    TMR0H = 0;
    TMR0L = 0;
}

uint16_t TMR0_read(void){
    contador = (TMR0L  | ((uint16_t)TMR0H << 8));
    return contador;
}

void TMR0_reset(void){
    TMR0H = 0;
    TMR0L = 0;
}

void TMR0_enable(void){
    T0CONbits.TMR0ON = 1;   // enables Timer0
}

void TMR0_disable(void){
    T0CONbits.TMR0ON = 0;   // stops Timer0
}