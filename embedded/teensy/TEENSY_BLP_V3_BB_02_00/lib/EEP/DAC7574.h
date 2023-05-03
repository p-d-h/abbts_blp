/**************************************************************************
    DAC7574 quad 12-bit DAC chip from Texas Instruments
    https://www.ti.com/product/DAC7574

    Written by Tryggvi Kr Tryggvason
    Grein Research ehf
    Iceland

**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#define MCP4726_CMD_WRITEDAC            (0x40)  // Writes data to the DAC
// unsigned char CMD_BYTES[4] = {0x08,0xA,0xC,0x16}; // Channels A,B,C,D
// CMD byte is with the bits 
// 00L1L0XSel1Sel0PD0
// 00 01 0 {00,01,10,11} 0
// 00010000
#define CMD_A  (0x10)
#define CMD_B  (0x12)
#define CMD_C  (0x14)
#define CMD_D  (0x16)

class DAC7574{
 public:
  DAC7574();
  void begin(uint8_t a);  
  void setVoltage( uint16_t outputvl, int channel);
  void setClock(uint16_t clk);
  private:
  uint8_t _i2caddr;
  uint16_t _i2c_clock;
};
