#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include "HAL.h"
#include "DATEN.h"
#include "CONTROLLER.h"
#include "SimpleModbusSlave.h"

#include "EEPrint.h"

// https://github.com/tonton81/FlexCAN_T4
#include <FlexCAN_T4.h>
FlexCAN_T4<CAN2, RX_SIZE_1024, TX_SIZE_256> Can2;
#define IO_PORT 33
#define MODBUS_REG_SIZE 256
unsigned int holdingRegs[MODBUS_REG_SIZE]; // function 3 and 16 register array
EEPrint eep;
int8_t byDummy;
int8_t bySemaphore = 0;

HAL::HAL() {
	;
}

void HAL::setup() {
	// Verbindung Teensy USB
	Serial.begin(115200);

	// Verbindung zum FPGA
	Serial7.setTX(29);
	Serial7.setRX(28); 
	Serial7.begin(230400);
	//Serial7.println("HAL SETUP");

	modbus_configure(115200, 1, 0, MODBUS_REG_SIZE, 1);
	

	// Test EEP
	//pinMode(A0, OUTPUT);


	pinMode(IO_SW_UP, INPUT);
	pinMode(IO_SW_DOWN, INPUT);
	pinMode(IO_SW_LEFT, INPUT);
	pinMode(IO_SW_RIGHT, INPUT);
	pinMode(IO_SW_OK, INPUT);

	pinMode(A16, INPUT);
	pinMode(A17, INPUT);

	pinMode(IO_PORT, OUTPUT);
	pinMode(IO_CS_FPGA, OUTPUT);
	pinMode(IO_CS_EXPANDER, OUTPUT);

	SPI.begin();
	SPI.beginTransaction(SPISettings(750000, MSBFIRST, SPI_MODE0));

	SPI1.setMOSI(26);
	SPI1.setMISO(39);
	SPI1.begin();
	SPI1.beginTransaction(SPISettings(7500000, MSBFIRST, SPI_MODE0));

	Can2.begin();
	Can2.setBaudRate(1000000);
	Can2.setMaxMB(64);
	Can2.enableFIFO();
	Can2.enableFIFOInterrupt();
	Can2.onReceive(can_receive);
	//Can2.mailboxStatus();

	this->spi_io_expander_setup();

	eep.setup();
}

u_int16_t state;
void HAL::extension_adc_dac(){
	eep.uiDac1 = this->can_.d.uiIn01;
	eep.uiDac2 = this->can_.d.uiIn02;

	switch(state) {
		case 0: 
			eep.update(0);
			state = 1;
			break;
		case 1: 
			eep.update(2);
			state = 2;
			break;
		case 2: 
			eep.update(1);
			state = 3;
			break;
		case 3: 
			eep.update(3);
			state = 0;
			break;
		default: 
			state = 0;
	}
	this->teensy.d.uiOut04 = eep.uiAdc1;
	this->teensy.d.uiOut05 = eep.uiAdc2;
}


void can_receive(const CAN_message_t &msg){
	//Serial7.println("C");
	//if (bySemaphore == 0){
		//bySemaphore = 1;

		switch(msg.id){
			case 0x200:
				hal.can_.d.byIn01 = msg.buf[0];
				hal.can_.d.byIn02 = msg.buf[1];
				hal.can_.d.byIn03 = msg.buf[2];
				hal.can_.d.byIn04 = msg.buf[3];
				hal.can_.d.byIn05 = msg.buf[4];	
				hal.teensy.d.byOut33 = msg.buf[6];	
				break;

			case 0x201:
				hal.teensy.d.byOut09 = msg.buf[0];
				hal.teensy.d.byOut10 = msg.buf[1];
				hal.teensy.d.byOut11 = msg.buf[2];
				hal.teensy.d.byOut12 = msg.buf[3];
				hal.teensy.d.byOut13 = msg.buf[4];
				hal.teensy.d.byOut14 = msg.buf[5];
				hal.teensy.d.byOut15 = msg.buf[6];
				hal.teensy.d.byOut16 = msg.buf[7];
				break;

			case 0x202:
				hal.teensy.d.byOut17 = msg.buf[0];
				hal.teensy.d.byOut18 = msg.buf[1];
				hal.teensy.d.byOut19 = msg.buf[2];
				hal.teensy.d.byOut20 = msg.buf[3];
				hal.teensy.d.byOut21 = msg.buf[4];
				hal.teensy.d.byOut22 = msg.buf[5];
				hal.teensy.d.byOut23 = msg.buf[6];
				hal.teensy.d.byOut24 = msg.buf[7];
				break;

			case 0x203:
				hal.teensy.d.byOut25 = msg.buf[0];
				hal.teensy.d.byOut26 = msg.buf[1];
				hal.teensy.d.byOut27 = msg.buf[2];
				hal.teensy.d.byOut28 = msg.buf[3];
				hal.teensy.d.byOut29 = msg.buf[4];
				hal.teensy.d.byOut30 = msg.buf[5];
				hal.teensy.d.byOut31 = msg.buf[6];
				hal.teensy.d.byOut32 = msg.buf[7];
				break;

			case 0x204:
				hal.can_.stream.arrByte[10] = msg.buf[0];
				hal.can_.stream.arrByte[11] = msg.buf[1];
				hal.can_.stream.arrByte[12] = msg.buf[2];
				hal.can_.stream.arrByte[13] = msg.buf[3];
				break;
		}

		//bySemaphore = 0;
	//}
}

void HAL::can(){
	CAN_message_t msg;
	//if (bySemaphore == 0){
		//bySemaphore = 1;

		msg.id = 0x100;
		msg.len = 8;
		msg.buf[0] = this->fpga.d.byIn08;
		msg.buf[1] = 0x00;
		msg.buf[2] = this->teensy.d.byOut02;
		msg.buf[3] = this->teensy.d.byOut03;
		msg.buf[4] = this->teensy.d.byOut04;
		msg.buf[5] = this->teensy.d.byOut05;
		msg.buf[6] = this->teensy.d.byOut06;
		Can2.write(msg);

		msg.id = 0x101;
		msg.len = 8;
		msg.buf[0] = this->teensy.stream.arrByte[35];
		msg.buf[1] = this->teensy.stream.arrByte[34];
		msg.buf[2] = this->teensy.stream.arrByte[37];
		msg.buf[3] = this->teensy.stream.arrByte[36];
		msg.buf[4] = this->teensy.stream.arrByte[39];
		msg.buf[5] = this->teensy.stream.arrByte[38];
		msg.buf[6] = 0x00;
		msg.buf[7] = 0x00;	
		Can2.write(msg);

		msg.id = 0x102;
		msg.len = 8;
		msg.buf[0] = this->teensy.stream.arrByte[41];
		msg.buf[1] = this->teensy.stream.arrByte[40];
		msg.buf[2] = this->teensy.stream.arrByte[43];
		msg.buf[3] = this->teensy.stream.arrByte[42];
		msg.buf[4] = 0x00;
		msg.buf[5] = 0x00;
		msg.buf[6] = 0x00;
		msg.buf[7] = 0x00;	
		Can2.write(msg);




		//bySemaphore = 0;
	//}
}

void HAL::modbus_rtu() {
  	modbus_update(holdingRegs);
	//holdingRegs[0]++;
	//holdingRegs[1] = holdingRegs[101]+10;
}

void HAL::input() {
	if (digitalRead(IO_SW_UP) != 0) this->bSwUp = 0; else this->bSwUp = 1;
	if (digitalRead(IO_SW_DOWN) != 0) this->bSwDown = 0; else this->bSwDown = 1;
	if (digitalRead(IO_SW_LEFT) != 0) this->bSwLeft = 0; else this->bSwLeft = 1;
	if (digitalRead(IO_SW_RIGHT) != 0) this->bSwRight = 0; else this->bSwRight = 1;
	if (digitalRead(IO_SW_OK) != 0) this->bSwOk = 0; else this->bSwOk = 1;
}

void HAL::output() {
	;
}

void HAL::transfer_io_expander(void) {
	//if (bySemaphore == 0){
		//bySemaphore = 1;

		digitalWrite(IO_CS_EXPANDER, LOW);
		this->spi_io_exp_in[0] = SPI1.transfer(this->spi_io_exp_out[0]);
		this->spi_io_exp_in[1] = SPI1.transfer(this->spi_io_exp_out[1]);
		this->spi_io_exp_in[2] = SPI1.transfer(this->spi_io_exp_out[2]);
		digitalWrite(IO_CS_EXPANDER, HIGH);
		delayMicroseconds(5);
		
		//bySemaphore = 0;
	//}
}

void HAL::spi_io_expander_setup(void) {
	// Aktivierung der Adressierung
	this->spi_io_exp_out[0] = 0x00;     this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = 0x00;     this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = 0x00;     this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = 0x00;     this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = 0x00;     this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled

	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = IOCON;   this->spi_io_exp_out[2] = 0b00101000; this->transfer_io_expander();// 0x28 sequential operation mode disabled, address mode enabled

	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = IODIRA;  this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// direction PORT A, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = IPOLA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// polarity PORT A, 0 = same, 1 = invert
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = IODIRB;  this->spi_io_exp_out[2] = 0b11100000; this->transfer_io_expander();// direction PORT B, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPPUA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPPUB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE

	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = IODIRA;  this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// direction PORT A, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = IPOLA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// polarity PORT A, 0 = same, 1 = invert
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = IODIRB;  this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// direction PORT B, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = GPPUA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
	this->spi_io_exp_out[0] = ADR2_W;  this->spi_io_exp_out[1] = GPPUB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE


	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = IODIRA;  this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// direction PORT A, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = IPOLA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// polarity PORT A, 0 = same, 1 = invert
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = IODIRB;  this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// direction PORT B, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = GPPUA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = GPPUB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE

	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = IODIRA;  this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// direction PORT A, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = IPOLA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// polarity PORT A, 0 = same, 1 = invert
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = IODIRB;  this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// direction PORT B, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = GPPUA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = GPPUB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE

	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// reset outputs
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = IODIRA;  this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// direction PORT A, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = IPOLA;   this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// polarity PORT A, 0 = same, 1 = invert
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = IODIRB;  this->spi_io_exp_out[2] = 0b00000000; this->transfer_io_expander();// direction PORT B, 0 = OUTPUT, 1 = INPUT
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = GPPUA;   this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = GPPUB;   this->spi_io_exp_out[2] = 0b11111111; this->transfer_io_expander();// pull-up resistor for corresponding input, 0 = INACTIVE, 1 = ACTIVE
}

void HAL::spi_io_expander_input_isr(void) {
	this->teensy.d.byOut01 = UC_VERSION_TEENSY;

	static uint8_t bEncA, bEncB;
	static uint8_t bEncArE, bEncBrE, bEncAfE, bEncBfE, bEncAold, bEncBold;
	
	this->spi_io_exp_out[0] = ADR1_R;  this->spi_io_exp_out[1] = GPIOB;   this->transfer_io_expander();	this->teensy.d.byOut02 = this->spi_io_exp_in[2];

	if (this->teensy.d.byOut02 & 0b00100000) bEncA = true; else bEncA = false;
	if (this->teensy.d.byOut02 & 0b01000000) bEncB = true; else bEncB = false;
	this->teensy.d.byOut02 = this->teensy.d.byOut02 & 0b11111100;

	/*
	if (bEncA && (bEncA != bEncAold) && !bEncB) bEncArE = true;
	else bEncArE = false;
	bEncAold = bEncA;

	if (bEncB && (bEncB != bEncBold) && !bEncA) bEncBrE = true;
	else bEncBrE = false;
	bEncBold = bEncB;

	if (bEncArE){
		this->teensy.d.iOutCounterEncoder--;
	}

	if (bEncBrE){
		this->teensy.d.iOutCounterEncoder++;
	}
	*/

	if (bEncA && (bEncA != bEncAold) && !bEncB) bEncArE = true;
	else bEncArE = false;
	if (!bEncA && (bEncA != bEncAold) && bEncB) bEncAfE = true;
	else bEncAfE = false;
	bEncAold = bEncA;

	if (bEncB && (bEncB != bEncBold) && !bEncA) bEncBrE = true;
	else bEncBrE = false;
	if (!bEncB && (bEncB != bEncBold) && bEncA) bEncBfE = true;
	else bEncBfE = false;
	bEncBold = bEncB;

	if (bEncArE || bEncAfE){
		this->teensy.d.iOutCounterEncoder--;
	}

	if (bEncBrE || bEncBfE){
		this->teensy.d.iOutCounterEncoder++;
	}

	
	this->spi_io_exp_out[0] = ADR2_R;  this->spi_io_exp_out[1] = GPIOA;   this->transfer_io_expander();	this->teensy.d.byOut03 = this->spi_io_exp_in[2];	
	//this->spi_io_exp_out[0] = ADR2_R;  this->spi_io_exp_out[1] = GPIOB;   this->transfer_io_expander();	this->teensy.d.byOut03 = this->spi_io_exp_in[2];	
	this->spi_io_exp_out[0] = ADR3_R;  this->spi_io_exp_out[1] = GPIOA;   this->transfer_io_expander();	this->teensy.d.byOut04 = this->spi_io_exp_in[2];
	this->spi_io_exp_out[0] = ADR4_R;  this->spi_io_exp_out[1] = GPIOA;   this->transfer_io_expander();	this->teensy.d.byOut05 = this->spi_io_exp_in[2];
	this->spi_io_exp_out[0] = ADR5_R;  this->spi_io_exp_out[1] = GPIOA;   this->transfer_io_expander();	this->teensy.d.byOut06 = this->spi_io_exp_in[2];
}

void HAL::spi_io_expander_output_isr(void) {
	digitalWrite(IO_PORT, in.bClk10Hz);
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPIOA;   this->spi_io_exp_out[2] = this->can_.d.byIn01; this->transfer_io_expander();
	this->spi_io_exp_out[0] = ADR1_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = this->can_.d.byIn02; this->transfer_io_expander();
	this->spi_io_exp_out[0] = ADR3_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = this->can_.d.byIn03; this->transfer_io_expander();
	this->spi_io_exp_out[0] = ADR4_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = this->can_.d.byIn04; this->transfer_io_expander();
	this->spi_io_exp_out[0] = ADR5_W;  this->spi_io_exp_out[1] = GPIOB;   this->spi_io_exp_out[2] = this->can_.d.byIn05; this->transfer_io_expander();
}

void HAL::input_isr(void) {
	controller.poti1_in = (uint16_t)(analogRead(A16));
	this->teensy.d.uiOut01 = controller.poti1_out;
	controller.poti2_in = (uint16_t)(analogRead(A17));
	this->teensy.d.uiOut02 = controller.poti2_out;
	
	if (this->fpga.d.byIn07 & 0b00000001) this->in.bFpgaButton = true; else this->in.bFpgaButton = false;
	if (this->fpga.d.byIn07 & 0b00100000) this->in.bClk1Hz = true; else this->in.bClk1Hz = false;
	if (this->fpga.d.byIn07 & 0b01000000) this->in.bClk5Hz = true; else this->in.bClk5Hz = false;
	if (this->fpga.d.byIn07 & 0b10000000) this->in.bClk10Hz = true; else this->in.bClk10Hz = false;
}

void HAL::output_isr(void) {

	// this->teensy.d.byOut2 = this->teensy.d.byOut1;

	// this->teensy.d.iOut07 = this->fpga.d.iIn07 + 10;

	/*
	this->teensy.d.byOut1  = this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += this->in.bClk1Hz; this->teensy.d.byOut1 = teensy.d.byOut1 << 1;
	this->teensy.d.byOut1 += false; 
	*/


	/*
	digitalWrite(LED1, this->bLed1);
	digitalWrite(LED2, this->bLed2);
	digitalWrite(LED3, this->bLed3);
	digitalWrite(LED4, this->bLed4);
	digitalWrite(LED5, this->bLed5);
	*/
	
}

void HAL::spi_fpga_transfer_isr(void) {
	byte n;

	digitalWriteFast(IO_CS_FPGA, 0);
	for (n = 0; n < 64; n++) {
		this->fpga.stream.arrByte[n] = SPI.transfer(this->teensy.stream.arrByte[n]);
	}
	digitalWriteFast(IO_CS_FPGA, 1);
}

HAL hal;
