#ifndef _EEPrint_H_
#define _EEPrint_H_
#include <Arduino.h>

//https://github.com/kibbi10/Arduino-DAC7574
//https://github.com/lesterwilliam/ADS7823

//Quelle Library: Github; Code Simon Schmid


class EEPrint {
public:
    // Input
	u_int16_t uiAdc1; //Input Wert Analog 1
	u_int16_t uiAdc2; //Input Wert Analog 1

	// Output
	u_int16_t uiDac1; //Output Wert Analog 1
    u_int16_t uiDac2; //Output Wert Analog 1

    EEPrint(void); //Konstruktor
	~EEPrint(void); //Destruktor
	void setup(void);
	void reset(void);
	void update(uint16_t state);

private:
    int       CLK; //Clock für Teensy I2C
     
};
# endif