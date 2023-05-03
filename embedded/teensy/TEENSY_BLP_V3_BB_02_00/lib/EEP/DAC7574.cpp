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

#include "DAC7574.h"
// unsigned char CMD_BYTES[4] = {0x08,0xA,0xC,0x16}; // Channels A,B,C,D

DAC7574::DAC7574() {
}

void DAC7574::begin(uint8_t addr) {
  _i2caddr = addr;
  //Wire1.begin();
  }

void DAC7574::setClock(uint16_t clk) {
  _i2c_clock = clk;
  //Wire1.setClock(clk);
  }


void DAC7574::setVoltage(uint16_t data, int channel)
{
    Wire1.beginTransmission(_i2caddr);
  // Write command based on channel
  if (channel == 0) {
    Wire1.write(CMD_A);
  } else if (channel == 1) {
    Wire1.write(CMD_B);
  } else if (channel == 2) {
    Wire1.write(CMD_C);
  } else if (channel == 3) {
    Wire1.write(CMD_D);
  }

  Wire1.write(data >> 4);
  Wire1.write(data << 4);
  Wire1.endTransmission();
}
