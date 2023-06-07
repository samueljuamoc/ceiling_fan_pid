/*
 * File:   main.c
 * Author: samuel jm
 */

#include "config.h"

uint8_t i,j;
//variables para lectura de luz
uint16_t LDR_0,LDR_1,LDR_2,LDR_3;
uint16_t luz;
//variables para lectura de velocidad
bool INT_overflow, indicador = 0;
uint16_t acum = 0;
//variables para salidas a plantas
uint16_t pwm_led, pwm_motor;
//funcion y variables para recepción de datos
uint8_t ch = 0;
uint8_t change_array = 0;
uint8_t string_pwm_led[5] = {0};
uint8_t string_pwm_motor[5] = {0};
__bit serial_read(uint8_t *s_pwm_led,uint8_t *s_pwm_motor);

void main(void){
    
    intosc_init();
    __delay_ms(200);
    USART_init(9600);
    __delay_ms(200);
    PORTA = 0b00000000;   //clearing latches
    TRISA = 0b11111111;   // all inputs 
    ADC_init();
    __delay_ms(200);
    TMR0_init();
    TMR1_init();
    TMR1_int_init();
    __delay_ms(200);
    pwm_set();
    __delay_ms(200);

    while(1){
        
        //lectura de velocidad por medio de contador e interrupciones
        TMR1_int_enable();      //enable timer overflow interruption       
        TMR0_enable();          //enables counter
        TMR0_reset();           //resets counter to 0s
        
        for(i=0;i<3;i++){
            TMR1_set();             //clean & start timer
            while(INT_overflow == 0)
                continue;           //count count count! until interruption(262ms)
            INT_overflow = 0;       //clear flag for interruption
            TMR1_stop();           //stop & clean timer
        }
        
        acum = TMR0_read();     //read counter (time elapsed: 786ms, x3 TMR1 time)
        TMR0_disable();         //disables counter
        TMR1_int_disable();     //disable timer overflow interruption

        //lectura de luz por medio de ADC y promediacion
        LDR_0 = ADC_read(0);
        LDR_1 = ADC_read(1);
        LDR_2 = ADC_read(2);
        LDR_3 = ADC_read(3);
        
        luz = (LDR_0+LDR_1+LDR_2+LDR_3)/4;
        
        //////////transmisión de valores de entrada para LABVIEW
        printf("%dA%dB",acum,luz);
        
        
        //////////reception of data from LABVIEW
        //acondicionamiento de nuestras string
        for(j=0;j<4;j++){
            string_pwm_led[j] = ' ';
            string_pwm_motor[j] = ' ';
        }
        string_pwm_led[4] = '\0';
        string_pwm_motor[4] = '\0';
        
        while(!serial_read(string_pwm_led,string_pwm_motor))
            continue;
        
        //conversion string to an integer
        pwm_led =   (uint16_t)atoi((const char *)string_pwm_led);
        pwm_motor = (uint16_t)atoi((const char *)string_pwm_motor);
        
        //send integer values to PWM output (values from 0 to 1000))
        pwm1_send(pwm_led);
        pwm2_send(pwm_motor);       
    }
}

__bit serial_read(uint8_t *s_pwm_led,uint8_t *s_pwm_motor){
    
    ch = getch();       // read the uartport, assign value to ch (code will be like: $,400,800,)
    
    if (ch == '$'){      // check if we have a $-sign, then we know it is the start of a sentence
    
        change_array = 0;       //variable helping changing of array  
        while(change_array < 3){ //while the data isnt finished

            ch = getch();

            if(ch == ','){
                change_array++;
                j=0;
            }
            else{
                switch(change_array){
                    case 1:
                        s_pwm_led[j++] = ch;
                    break;
                    case 2:
                        s_pwm_motor[j++] = ch;
                    break;
                    default:
                        //do nothing
                    break;
                }
            }     
        }
        return 1;  
    } 
    //if lecture wasnt $, read again until $ is received
    return 0;
}

//ISR(Interrupt Service Routine) of XC8 compiler has this format
__interrupt() void ISR1(void){
    INT_overflow = 1; //set bit of interrupt
    PIR1bits.TMR1IF = 0;            //clear overflow flag bit in software
}
//end of code.