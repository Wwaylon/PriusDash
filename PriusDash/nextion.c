/*
 * nextion.c
 *
 * Created: 4/25/2024 3:35:08 PM
 *  Author: Waylon
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "nextion.h"
#include "USART.h"
#include <math.h>
#include "can.h"

#define MAX_STRING_LENGTH 50

double round(double d)
{
	return floor(d + 0.5);
}



uint8_t input_available()
{
	return (UCSR0A & (1<<RXC0)); // 0 = no commands, 1 = commands in input stream
}
void receive_command(){
	char input[MAX_STRING_LENGTH] = "";
	char received_char = USART_Receive(stdin);
	while(received_char != 0xff)
	{
		size_t len = strlen(input);
		if (len < MAX_STRING_LENGTH - 1) {
			input[len] = received_char;
			input[len + 1] = '\0'; // Null-terminate the string
		}
		received_char = USART_Receive(stdin);
	}
	if(!strcmp("ON", input))
	{
		printf("ON-r\n");
	}else if(!strcmp("OFF", input))
	{
		printf("OFF-r\n");
	}
	memset(input, 0, sizeof(input));
}

void send_command(char command[])
{
	printf("%s", command);
	printf("ÿ");
	printf("ÿ");
	printf("ÿ");
}

void update_dash(struct CAN_frame *message)
{
	switch (message->id)
	{
		case 0x120:
			switch ((message->data[5] & 0x03))
			{
				case 0x00:
				send_command("mode.txt=\"P\"");
				break;
				case 0x01:
				send_command("mode.txt=\"R\"");
				break;
				case 0x02:
				send_command("mode.txt=\"N\"");
				break;
				case 0x03:
				send_command("mode.txt=\"D\"");
				break;
			}
		break;
		
		case 0x5b6: 
			switch ((message->data[2] & 0xc0))
			{
				case 0x00:
				send_command("doorstat.txt=\"All Closed\"");
				break;
				case 0x80:
				send_command("doorstat.txt=\"Driver Door\"");
				break;
				case 0x40:
				send_command("doorstat.txt=\"Back Doors\"");
				break;
			}
		break;
		
		case 0x57f:
			switch((message->data[1]) & 0x38)
			{
				case 0x00: //off
				send_command("light.pic=2");
				break;
				case 0x10: //parkers lights
				send_command("light.pic=43");
				break;
				case 0x30: //low beam
				send_command("light.pic=43");
				break;
				case 0x38: //high beam
				send_command("light.pic=42");
				break;
			}
		break;
		
		case 0x3ca:
			; //need this null statement cause declarations are not considered statements??(weird) Labels may only precede statements
			uint8_t speedm = message->data[2] * 0.621; //mph
			printf("mph.val=%d", speedm);
			printf("ÿ");
			printf("ÿ");
			printf("ÿ");
		break;
		
		case 0x3cb:
			;
			uint8_t soc = (256 * message->data[2] + message->data[3]) / 2;
			printf("soc.val=%d", soc);
			printf("ÿ");
			printf("ÿ");
			printf("ÿ");
		break;
		
		case 0x5a4:
			; //0-2c output is 0-100
			uint8_t tanklevel = round(2.27 * message->data[1]);
			printf("tanklevel.val=%d", tanklevel);
			printf("ÿ");
			printf("ÿ");
			printf("ÿ");
		break;
		
		case 0x7e8:
			;
			uint16_t rpm = (256 * message->data[3] + message->data[4])/4;
			printf("rpm.val=%d", rpm);
			printf("ÿ");
			printf("ÿ");
			printf("ÿ");
	
	}
	

}



