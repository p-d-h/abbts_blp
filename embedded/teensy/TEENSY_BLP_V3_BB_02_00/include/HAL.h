#ifndef _HAL_H_
#define _HAL_H_

#define UC_VERSION_TEENSY 1

#define ENCODER_TIME 30


#include "HAL_IN.h"
#include "HAL_OUT.h"
#include <FlexCAN_T4.h>

#define IODIRA 0x00 // data direction register for PORTA   
#define IODIRB 0x01 // data direction register for PORTB
#define IPOLA  0x02 // input polarity register for PORTA
#define IPOLB  0x03 // input polarity register for PORTB
#define IOCON  0x0A // configuration register for device       
#define GPPUA  0x0C // 100kOhm pullup resistor register for PORTA (sets pin to input when set)   
#define GPPUB  0x0D // 100kOhm pullup resistor register for PORTB (sets pin to input when set)       
#define GPIOA  0x12 // general purpose I/O register for PORTA 
#define GPIOB  0x13 // general purpose I/O register for PORTB

#define ADR1_W 0b01000010 
#define ADR1_R 0b01000011 
#define ADR2_W 0b01000100 
#define ADR2_R 0b01000101 
#define ADR3_W 0b01000110
#define ADR3_R 0b01000111
#define ADR4_W 0b01001000
#define ADR4_R 0b01001001
#define ADR5_W 0b01001010 
#define ADR5_R 0b01001011 


#define IO_SW_UP 2
#define IO_SW_DOWN 3
#define IO_SW_LEFT 4
#define IO_SW_RIGHT 5
#define IO_SW_OK 6

#define IO_CS_FPGA 10
#define IO_CS_EXPANDER 38

typedef union {
  struct {
    uint8_t byOut01;
    uint8_t byOut02;
    uint8_t byOut03;
    uint8_t byOut04;
    uint8_t byOut05;
    uint8_t byOut06;
    uint8_t byOut07;
    uint8_t byOut08;
    uint8_t byOut09;
    uint8_t byOut10;
    uint8_t byOut11;
    uint8_t byOut12;
    uint8_t byOut13;
    uint8_t byOut14;
    uint8_t byOut15;
    uint8_t byOut16;
    uint8_t byOut17;
    uint8_t byOut18;
    uint8_t byOut19;
    uint8_t byOut20;
    uint8_t byOut21;
    uint8_t byOut22;
    uint8_t byOut23;
    uint8_t byOut24;
    uint8_t byOut25;
    uint8_t byOut26;
    uint8_t byOut27;
    uint8_t byOut28;
    uint8_t byOut29;
    uint8_t byOut30;
    uint8_t byOut31;
    uint8_t byOut32;
    uint8_t byOut33;
    uint8_t byOut34;   
    uint16_t uiOut01;
    uint16_t uiOut02;
    int16_t iOutCounterEncoder;
    uint16_t uiOut04;// ADC1
    uint16_t uiOut05;// ADC2
    int16_t iOut06;
    int16_t iOut07;
    int16_t iOut08;
    int16_t iOut09;
    int16_t iOut10;
    int16_t iOut11;
    int16_t iOut12;
    int16_t iOut13;
    int16_t iOut14;
    int16_t iOut15;
  } d;
  struct {
    uint8_t arrByte[64];
  } stream;
}
sController;

typedef union {
  struct {
    uint8_t byIn01;
    uint8_t byIn02;
    uint8_t byIn03;
    uint8_t byIn04;
    uint8_t byIn05;
    uint8_t byIn06;
    uint8_t byIn07;
    uint8_t byIn08;
    uint8_t byIn09;
    uint8_t byIn10;
    uint16_t uiIn01;
    uint16_t uiIn02;
    int16_t iIn03;
    int16_t iIn04;
    int16_t iIn05;
    int16_t iIn06;
    int16_t iIn07;
    int16_t iIn08;
    int16_t iIn09;
    int16_t iIn10;
    int16_t iIn11;
    int16_t iIn12;
    int16_t iIn13;
    int16_t iIn14;
    int16_t iIn15;
    int16_t iIn16;
    int16_t iIn17;
    int16_t iIn18;
    int16_t iIn19;
    int16_t iIn20;
    int16_t iIn21;
    int16_t iIn22;
    int16_t iIn23;
    int16_t iIn24;
    int16_t iIn25;
    int16_t iIn26;
    int16_t iIn27;
  } d;
  struct {
    uint8_t arrByte[64];
  } stream;
}
sFpga;

void can_receive(const CAN_message_t &msg);

class HAL {
public:
	u_int8_t	bSwUp;
	u_int8_t	bSwDown;
	u_int8_t	bSwLeft;
	u_int8_t	bSwRight;
	u_int8_t	bSwOk;
	u_int8_t	sw_mask;
  u_int16_t uiADC1;
  u_int16_t uiADC2;
  
	HAL_IN in;
	HAL_OUT out;
	
	HAL(void);
	void setup(void);
  void extension_adc_dac(void);
  void modbus_rtu(void);
  void can(void);
  void input(void);
	void output(void);
  void spi_io_expander_setup(void);
  void spi_io_expander_input_isr(void);
  void spi_io_expander_output_isr(void);
	void input_isr(void);
	void output_isr(void);
	void spi_fpga_transfer_isr(void);

  sController teensy;
  sFpga fpga;
  sFpga can_;
  

private:
  void transfer_io_expander(void);

  byte spi_io_exp_in[3];
  byte spi_io_exp_out[3];
};

extern HAL hal;

# endif
