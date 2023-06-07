#include "config.h"

uint16_t contador;

void TMR1_init(void){
    T1CONbits.RD16 = 1;             //16 bit R/W (1)
    T1CONbits.T1RUN = 1;            //TMR1  oscillator device clock (1)
    T1CONbits.T1CKPS = 0b11;        //prescale value 1:8 (11) bit 5-4(Timer1 clock = 250kHz)
    T1CONbits.T1OSCEN = 1;          //TMR1 oscillator enable (1)
    //T1CONbits.T1SYNC bit ignored  //Ignored (0)  
    T1CONbits.TMR1CS = 0;           //Internal clock (Fosc/4) (0)
    T1CONbits.TMR1ON = 0;           //TMR1 set or stop (0)
}

void TMR1_set(void){
    TMR1H  = 0;           // reset Timer1
    TMR1L  = 0;
    T1CONbits.TMR1ON = 1;           //TMR1 set or stop (0)
}
/*//not necessary but could be useful
uint16_t TMR1_read(void){
    contador = (TMR1L  | ((uint16_t)TMR1H << 8));
    return contador;
}
*/
void TMR1_stop(void){
    T1CONbits.TMR1ON = 0;           //TMR1 set or stop (0)
    TMR1H  = 0;           // clean Timer1
    TMR1L  = 0;
}

void TMR1_int_init(void){//interrupts initiated
    INTCONbits.GIEH=1;              //Global Interrupt Enable bit
    INTCONbits.GIEL=1;              // Enables all unmasked peripheral interrupts
    RCONbits.IPEN=0;                //Disable priority levels on interrupts
    
    PIE1bits.TMR1IE = 1;            //Enables the TMR1 overflow interrupt
    PIR1bits.TMR1IF = 0;            //clear overflow flag bit in software
}

void TMR1_int_enable(void){
    INTCONbits.GIE=1;       //Global Interrupt Enable bit
}

void TMR1_int_disable(void){
    INTCONbits.GIE=0;       //Global Interrupt Enable bit
}
