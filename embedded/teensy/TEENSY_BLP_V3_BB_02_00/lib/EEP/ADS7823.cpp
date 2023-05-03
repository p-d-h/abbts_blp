#include "ADS7823.h"

ADS7823::ADS7823(byte address, float ref_voltage){
  _address = address;
  _ref_voltage = ref_voltage;
  init();
}

void ADS7823::init(){
}

void ADS7823::setClock(uint16_t clk) {
  // Wire1.setClock(clk);
}

int ADS7823::readADC(){
  Wire1.beginTransmission(_address);
  Wire1.write(command_byte);
  Wire1.endTransmission();
  
  Wire1.requestFrom(_address, 2);
  
  if(Wire1.available() <= 2){
    return ((Wire1.read()) << 8) | (Wire1.read());
  }
}

float ADS7823::readADCvoltage(){
  float value;
  Wire1.beginTransmission(_address);
  Wire1.write(command_byte);
  Wire1.endTransmission();
  
  Wire1.requestFrom(_address, 2);
  
  if(Wire1.available() <= 2){
    value = ((Wire1.read()) << 8) | (Wire1.read());
  }
  value = 3.3 * value / 4096.0;
  return value;
}

