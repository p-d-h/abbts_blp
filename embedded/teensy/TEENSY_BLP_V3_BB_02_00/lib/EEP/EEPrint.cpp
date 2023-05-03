//https://github.com/kibbi10/Arduino-DAC7574
//https://github.com/lesterwilliam/ADS7823

//Code Simon Schmid

#include "EEPrint.h"
#include <Arduino.h>
#include <Wire.h>
#include <ADS7823.h>
#include <DAC7574.h>


#define DAC_ADDR 0x4e
DAC7574 dac;

#define ADDRESS_ADC_1     0x48 //  1001 000
ADS7823 analogDigitalConverter_1(ADDRESS_ADC_1, 3.3); // I2C address and reference voltage in [V]

#define ADDRESS_ADC_2     0x49 //  1001 001
ADS7823 analogDigitalConverter_2(ADDRESS_ADC_2, 3.3); // I2C address and reference voltage in [V]

EEPrint::EEPrint(void) {
	// this->setup();
	// this->reset();
}

EEPrint::~EEPrint(void) {
    ;
}

void EEPrint::setup(void) {
    this->CLK = 400000;
    Wire1.begin();
    Wire1.setClock(this->CLK);
    dac.begin(DAC_ADDR);
}

void EEPrint::reset(void) {
    ;
}

void EEPrint::update(uint16_t state) {
    switch(state){
    case 0:
        this->uiAdc1 = analogDigitalConverter_1.readADC();
        break;
    case 1:
        this->uiAdc2 = analogDigitalConverter_2.readADC();
        break;
    case 2:
        dac.setVoltage(this->uiDac1, 0);
        break;
    case 3:
        dac.setVoltage(this->uiDac2, 1);
        break;
    }
}