#ifndef ADS7823_H
#define ADS7823_H

#include <Arduino.h>
#include <Wire.h>


class ADS7823{

  private:
    byte _address;
    float _ref_voltage;
    const int command_byte = 0x00;
    uint8_t _i2c_clock;
    

  public:
    ADS7823(byte _address, float ref_voltage);
    void init();
    int readADC();
    float readADCvoltage();
    void setClock(uint16_t clk);
};

#endif
