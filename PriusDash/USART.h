
#ifndef USART_H_
#define USART_H_
#include <stdio.h>

void USART_init();
int USART_Transmit(char u8Data, FILE *stream);
int USART_Receive(FILE *stream);
void UART_getLine(char* buf, uint8_t n);
void USART_flush(void);

#endif /* USART_H_ */