/*
 * can.h
 *
 * Created: 3/29/2024 6:08:01 PM
 *  Author: Waylon
 */ 

#ifndef CAN_H_
#define CAN_H_

#define CNF1 0x2A
#define CNF2 0x29
#define CNF3 0x28

#define CANSTAT 0xE
#define CANCTRL 0xf
#define TXB0CTRL 0x30
#define TXB1CTRL 0x40
#define TXB2CTRL 0x50

#define TXREQ 3

#define WRITE_INSTRUCTION 0x02
#define READ_INSTRUCTION 0x03
#define BITMODIFY_INSTRUCTION 0x05
#define RESET_INSTRUCTION 0xC0
#define READ_STATUS_INSTRUCTION 0xA0
#define RTS_TXB0 0x81
#define RTS_TXB1 0x82
#define RTS_TXB2 0x84

#define CANINTE 0x2B
#define MERRE 0x7
#define WAKIE 0x6
#define ERRIE 0x5
#define TX2IE 0x4
#define TX1IE 0x3
#define TX0IE 0x2
#define RX1IE 0x1
#define RX0IE 0x0

#define CANINTF 0x2C
#define RX0IF 0
#define RX1IF 1
#define RXB0CTRL 0x60
#define RXB1CTRL 0x70
#define RXB0SIDH 0x61
#define RXB1SIDH 0x71
#define RXB0SIDL 0x62
#define RXB1SIDL 0x72
#define RXB0EID8 0x63
#define RXB1EID8 0x73
#define RXB0EID0 0x64
#define RXB1EID0 0x74
#define RXB0DLC 0x65
#define RXB1DLC 0x75
#define RXB0D 0x66
#define RXB1D 0x76

#define RXF0SIDH 0x00
#define RXF1SIDH 0x04
#define RXF2SIDH 0x08
#define RXF3SIDH 0x10
#define RXF4SIDH 0x14
#define RXF5SIDH 0x18

#define RXF0SIDL 0x01
#define RXF1SIDL 0x05
#define RXF2SIDL 0x09
#define RXF3SIDL 0x11
#define RXF4SIDL 0x15
#define RXF5SIDL 0x19

#define RXF0EDI8 0x02
#define RXF1EDI8 0x06
#define RXF2EDI8 0x0A
#define RXF3EDI8 0x12
#define RXF4EDI8 0x16
#define RXF5EDI8 0x1A

#define RXF0EID0 0x03
#define RXF1EID0 0x07
#define RXF2EID0 0x0B
#define RXF3EID0 0x13
#define RXF4EID0 0x17
#define RXF5EID0 0x1B

#define RXM0SIDH 0x20
#define RXM1SIDH 0x24

#define RXM0SIDL 0x21
#define RXM1SIDL 0x25

#define RXM0EID8 0x22
#define RXM1EID8 0x26

#define RXM0EID0 0x23
#define RXM1EID0 0x27

#define BUKT 2
#define BUKT1 1
#define EXIDE 3

enum MCP2515_MODE {	
	NORMAL_MODE = 0x0,
	SLEEP_MODE = 0x1,
	LOOPBACK_MODE = 0x2,
	LISTEN_ONLY_MODE = 0x3,
	CONFIGURATION_MODE = 0x4
};

enum MCP2515_CLK_FREQ{
	MCP2515_16MHZ,
	MCP2515_8MHZ
};

enum MCP2515_BAUD{
	MCP2515_1000KBPS,
	MCP2515_500KBPS,
	MCP2515_250KBPS,
	MCP2515_125KBPS,
	MCP2515_100KBPS,
	MCP2515_50KBPS
};

enum RECEIVE_STATUS {
	MSG_RECEIVED,
	MSG_NOT_RECEIVED	
};

enum MESSAGE_PRIORITY{
	HIGH_PRIORITY = 0x3,
	HIGH_INTERMEDIATE_PRIORITY = 0x2,
	LOW_INTERMEDIATE_PRIORITY = 0x1,
	LOW_PRIORITY = 0
};

enum MASK_ID{
	MASK0,
	MASK1
};

enum FILTER_ID{
	FILTER0,
	FILTER1,
	FILTER2,
	FILTER3,
	FILTER4,
	FILTER5,
};

struct CAN_frame{
	uint8_t CAN_standard; // 0 for standard; 1 for extended can frames
	uint8_t priority;
	uint16_t id;
	uint8_t rtr_bit;
	uint8_t dlc;
	uint8_t data[8];
};

void MCP2515_init(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ);
void MCP2515_reset();
void MCP2515_writeReg(uint8_t address, uint8_t value);
uint8_t MCP2515_readReg(uint8_t address);
void MCP2515_readRegs(uint8_t address, uint8_t read_values[], uint8_t bytes);
uint8_t MCP2515_setBitTimingCustom(uint8_t cnf1_a, uint8_t cnf2_a, uint8_t cnf3_a);
void MCP2515_bitModify(uint8_t address, uint8_t mask, uint8_t value);
uint8_t MCP2515_setBitTiming(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ);
uint8_t MCP2515_getMode();
void MCP2515_setMode(const enum MCP2515_MODE mode);
void MCP2515_sendTestMessage();
void MCP2515_sendMessage();
void MCP2515_RTS();
enum RECEIVE_STATUS MCP2515_receiveMessageStatus();
uint8_t MCP2515_readStatus();
void MCP2515_getMessage(struct CAN_frame *message);
void MCP2515_sendMessage(struct CAN_frame message);
void MCP2515_setFilter(enum FILTER_ID filter, uint32_t filter_value, uint8_t extended);
void MCP2515_setMask(enum MASK_ID mask, uint32_t mask_value);
void MCP2515_enableInterrupt();


#endif /* CAN_H_ */