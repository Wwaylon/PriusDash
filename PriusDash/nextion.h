/*
 * nextion.h
 *
 * Created: 4/25/2024 3:34:51 PM
 *  Author: Waylon
 */ 


#ifndef NEXTION_H_
#define NEXTION_H_

#include "can.h"

uint8_t input_available();
void receive_command();
void update_dash(struct CAN_frame *message);
void send_command(char command[]);
void request_RPM();



#endif /* NEXTION_H_ */