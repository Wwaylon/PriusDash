/*
 * spi.c
 *
 * Created: 3/29/2024 6:08:01 PM
 *  Author: Waylon
 */ 
#include <avr/io.h>
#include <stdint.h>
#include "SPI.h"

//SPI INIT
/*
Initializes SPI to some general settings. For more granular control of setting, would suggest manually changing SPCR rather than using this function.
*/
void SPI_init()
{
	//
	PRR &= ~(1<<PRSPI);
	//Set SCK, MOSI, SS to output
	DDRB |= (1<<SCK) | (1<<MOSI) | (1<<SS);
	PORTB |= (1<<SS);
	//Enable spi, set as master, set speed to fclk/16
	//SPCR |= (1<<SPE) | (1<<MSTR)  | (1 << SPR0);
	SPCR |= (1<<SPE) | (1<<MSTR)  | (1 << SPI2X);
}

//SS_low
/*
Used to signal slave of incoming SPI transmission
*/
void SS_low(){
	PORTB &= ~(1<<SS);
}

//SS_high
/*
Used to signal slave end of incoming SPI transmission
*/
void SS_high(){
	PORTB |= (1<<SS);
}

//SPI_masterTransmit
/*
Used to send 1 byte of data via SPI. Change additional calls of this function before SS goes high to send more than 1 byte.
*/
void SPI_masterTransmit(uint8_t data)
{
	//load data
	SPDR = data;
	//Wait for transmission to complete
	while(!(SPSR & (1<<SPIF)))
	{
	}
}

uint8_t SPI_masterReceive()
{
	// Transmit anything
	SPDR = 0xFF;
	// Wait for reception complete
	while(!(SPSR & (1 << SPIF)));
	// return data register
	return SPDR;
}
