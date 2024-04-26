/*
 * spi.h
 *
 * Created: 3/29/2024 6:08:01 PM
 *  Author: Waylon
 */ 

#ifndef SPI_H_
#define SPI_H_

#define SCK 5
#define MISO 4
#define MOSI 3
#define SS 2 

void SPI_init();
uint8_t SPI_masterReceive();
void SPI_masterTransmit(uint8_t data);
void SS_high();
void SS_low();

#endif /* SPI_H_ */