#include "config.h"

//10bit resolution = 1024 combinations
//min value: 0 ; Max value: 1023
//V de referencia 5V -> adc = 5/1024 = 4.8mV 1 bit
//Osc time: 8 MHz. Tosc = 1/8MHz = 125ns = 0.125us

// 0.8us < TAD < 25us
// 8*Tosc = (125ns)(8) = 1us (right for TAD)      (8*Tosc)
// 16*Tosc = nope
// por datasheet: 2.45us < xTAD
//TACQ = 4 * 1us = 4 us ; its >2.45us so its okay (4*TAD)
//So here: Tosc = 0.125us ; TAD = 1us ; TACQ = 4us

void ADC_init(void){    //Initialize AN pins
    ADCON1bits.VCFG = 0b00;       //V reference points (0 - 5 V)
    ADCON1bits.PCFG = 0b1011;     //set AN or D-I/O inputs (AN(0,1,2,3) enabled here)
    ADCON0 = 0;                 // enable ADC register, for now we set it as disabled
    ADCON2bits.ACQT = 0b010;    //TACQ = 4*TAD
    ADCON2bits.ADCS = 0b001;    //Fosc/8
    ADCON2bits.ADFM = 1;        //result format right justified
}

uint16_t ADC_read(uint8_t canal){   //reads AN(0-12) pin, return 0-1023 value in a uint format
    ADCON0 = 0;                 //clearing register, enable ADC
    ADCON0bits.CHS = canal;     //select AN channel (0-12)
    ADCON0bits.ADON = 1;        //enable ADC module
    ADCON0bits.GODONE = 1;      //start conversion
    while(ADCON0bits.GODONE == 1)  //don't continue until conversion is finished
        continue;
    ADCON0bits.ADON = 0;        //disable ADC module
    
    return ADRES;
}
