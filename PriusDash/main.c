/*
 * PriusDash.c
 *
 * Created: 4/25/2024 6:45:57 PM
 * Author : Waylon
 */ 
#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include "USART.h"
#include "nextion.h"
#include <util/delay.h>
#include "can.h"
#include <avr/interrupt.h>

#define BUFFER_SIZE 10

struct CircularBuffer
{
	struct CAN_frame buffer[BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
};

struct CircularBuffer cb;

ISR(INT0_vect)
{
	// Write CAN message into buffer
	MCP2515_getMessage(&cb.buffer[cb.head]);
	cb.head = (cb.head + 1) % BUFFER_SIZE; // Increment head circularly
	if (cb.head == cb.tail)
	{
		// Buffer is full, move tail to overwrite oldest message
		cb.tail = (cb.tail + 1) % BUFFER_SIZE;
	}
}


void bufferInit()
{
	cb.head = 0;
	cb.tail = 0;
}

struct CAN_frame *bufferRead()
{
	if (cb.head == cb.tail) // Check if buffer is empty
	{
		return NULL;
	}
	else
	{
		struct CAN_frame *message = &cb.buffer[cb.tail];
		cb.tail = (cb.tail + 1) % BUFFER_SIZE; // Increment tail circularly
		return message;
	}
}

int main(void)
{
	USART_init();
	MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
	MCP2515_enableInterrupt();
	DDRD &= ~(1 << 2);
	PORTD |= (1<<2); //pull up
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	EIMSK |= (1<<INT0);
	sei();
	bufferInit();
	struct CAN_frame *message;
	
    while (1) 
    {
		if (input_available())
		{
			receive_command();
		}
		message = bufferRead();
		if (message != NULL)
		{
			update_dash(message);
		}
    }
}

