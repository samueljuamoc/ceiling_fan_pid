#include "config.h"

void pwm_set(void){
    ////////////////////PWM
    PORTC = 0x00; //clearing latches
    PORTB = 0x00;
    TRISCbits.RC2 = 0;   //CCP1 as output
    TRISBbits.RB3 = 0;   //CCP2 as output
    
    // PWM period = (PR2 + 1) * 4 * Tocs * TMR2 Prescaler
    // 1/PWM frec = PWMperiod
    //eligiendo TMR2_pre = 16
    // 1 / 500 Hz = (PR2 + 1) * 4 * (1/8MHz) * 16
    //PR2 no mayor a 255, ya que es una localidad de un byte
    //PR2 = ((1/500)/(4*(1/8M)*16)) - 1 = 249 = 0xF9
    
    //obtenemos el valor de 100% en binario. forma 1:
    //PWM duty cycle 100%_bits = (Fosc_micro*periodoausar_PWM)/ TMR2_Pre
    //((8M)(1/500))/(16) = 1000
    //forma 2:
    //PWM duty cycle 100%_period = Tosc*CCPRXL:CCPXCON* TMR2_Pre
    //CCPRXL = PWM_period/(Tosc*TMR2_pre)
    //  = 1000 = 100%
    
    //two LSBs (bit 1 & 0) of the 10-bit PWM dutycycle are in CCP1CON.5 & .4
    // the 8 MSBs are in CCPR1L
    // 50% = 500 = 0b 01 1111 0100
    //So dividing would be:
    //CCPR1L:    01 1111 01
    //CCP1CON(5y4):   00
    //for example 250 = 00 1111 1010
    //set to zero duty cycle to initialize
    PR2 = 249;         //value of TMR2_prescaler = 249
    
    CCPR1L = 0b00000000;    //8 MSBs
    CCP1CONbits.DC1B1 =0;   //2nd LSB (5th bit)
    CCP1CONbits.DC1B0 =0;   //LSB     (4th bit)
    CCP1CONbits.CCP1M = 0b1100; //set PWM mode

    //doing the same with CCP2
    CCPR2L = 0b00000000;    //8 MSBs
    CCP2CONbits.DC2B1 =0;   //2nd LSB (5th bit)
    CCP2CONbits.DC2B0 =0;   //LSB     (4th bit)
    CCP2CONbits.CCP2M = 0b1100; //set PWM mode
    
    //timer2
    T2CONbits.T2CKPS = 0b11;   //prescaler 16
    TMR2 = 0; //set tmr2 to zero
    T2CONbits.TMR2ON = 1;   //SET tmr2 on 
}

void pwm1_send(uint16_t valor){
    //valor has to be in the range of 0-1000
    //moving a value to the PWM %cycle but using a variable
    CCPR1L = (valor >> 2) & 0xFF;    //8 MSBs
    CCP1CONbits.DC1B1 = valor & (1<<0);   //2nd LSB (5th bit)
    CCP1CONbits.DC1B0 = valor & (1<<1);   //LSB     (4th bit)
}

void pwm2_send(uint16_t valor){
    //valor has to be in the range of 0-1000
    //moving a value to the PWM %cycle but using a variable
    CCPR2L = (valor >> 2) & 0xFF;    //8 MSBs
    CCP2CONbits.DC2B1 = valor & (1<<0);   //2nd LSB (5th bit)
    CCP2CONbits.DC2B0 = valor & (1<<1);   //LSB     (4th bit)
}