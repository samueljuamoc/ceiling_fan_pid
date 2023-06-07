#include "config.h"

void intosc_init(void){
    //////////////////INT OSC (of 8 MHz)
    //OSCTUNEbits.INTSRC = 0; //31kHz low freq source clock
    //OSCTUNEbits.TUN = 0b00000; //center freq, 4MHz
    //OSCCONbits.SCS = 0b00;    //sleep mode (?)
    OSCCONbits.IRCF = 0b111;  //8MHz
    OSCCONbits.IOFS = 1;    //stable freq
    OSCCONbits.SCS = 0b11;    //system clock using internal osc
}