# ceiling_fan_pid

This is the code used for creating a self made DAQ system using the PIC18F4550 microcontroller.
All the files included here are the content of the .X MPLAB project directory. XC8 compiler was used.

We have the following libraries:
- usart_lib.h : This library allows us to communicate with LabVIEW (in this case) using the UART protocol.
- adc_lib.h : This library allows us to use the ADCs.
- intosc_lib.h : This library allows us to use the internal oscillator of the microcontroller.
- pwm_lib.h : This library allows us to use the 2 PWM modules.
- timer0_lib.h : This library allows us to use the TMR0 as a counter.
- timer1_lib.h : This library allows us to use the TMR1 as a timer with overflow interruption.

The config.h header helps with the processor files of the PIC18F4550, as well as the Configuration Bits, the constant of the clock and all the inclusion of libraries.

The main.c is the code of the DAQ system: Inclusion of config.h file, defining variables to be used, initializing everything, and looping these steps:
1. Reading of the velocity of a motor through counter and interrupts.
2. Reading of the ADCs in order to get intensity of light.
3. Conditioning and transmission of readings in form of a data stream to LabVIEW.
4. Reception and conditioning of LabVIEW data stream (PID controlled closed-loop system values).
5. Rewrite of the PWM outputs.
