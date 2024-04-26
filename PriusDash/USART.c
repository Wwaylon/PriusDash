#include "USART.h"
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#define BAUD 57600
#define BAUD_TOL   2
#include <util/setbaud.h>

static void uart_57600(void)
{
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
}

int USART_Transmit(char u8Data, FILE *stream)
{
	while (!(UCSR0A & (1<<UDRE0)))
	;
	UDR0 = u8Data;
	return 0;
}



int USART_Receive(FILE *stream)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)))
	;
	/* Get and return received data from buffer */
	return UDR0;
}


void USART_init(){
	static FILE uart0_str = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_RW);
	stdin = stdout = &uart0_str;
	uart_57600();
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	//enable receiver transceiver w/ interrupts
	UCSR0C |= (3<< UCSZ00); // 8bit
	UCSR0C &= ~(1<< USBS0); // 1 stop bit
	
	USART_flush();
}

void UART_getLine(char* buf, uint8_t n)
{
	uint8_t bufIdx = 0;
	char c;

	do
	{
		c = USART_Receive(stdin);

		if (bufIdx < (n - 1)) {
			buf[bufIdx++] = c;
		}
	}
	while((bufIdx < (n - 1)) && (c != '\r'));

	buf[bufIdx] = '\0';
}


void USART_flush(void)
{
	unsigned char dummy;
	while (UCSR0A & (1<<RXC0)) dummy = UDR0;
}
