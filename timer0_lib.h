#ifndef TIMER0_LIB_H
#define TIMER0_LIB_H

void TMR0_init(void);
uint16_t TMR0_read(void);
void TMR0_reset(void);
void TMR0_enable(void);
void TMR0_disable(void);

#endif