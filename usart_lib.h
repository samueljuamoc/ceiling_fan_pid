#ifndef USART_LIB_H
#define USART_LIB_H

void USART_init(long BAUD);
void putch(uint8_t data);//called like this we can use the stdout printf
uint8_t getch();    //called like this we can use the stdin scanf
void UART_print(char *data);

#endif