#ifndef _CONTROLLER_ISR_H_
#define _CONTROLLER_ISR_H_

#include "DATEN.h"
#include "pt1.h"

class CONTROLLER {
public:
	uint16_t poti1_in;
	uint16_t poti2_in;
	uint16_t poti1_out;
	uint16_t poti2_out;
	
	

	CONTROLLER(void);
    ~CONTROLLER(void);
	void setup(void);
	void reset(void);
	void cyclic(void);
	void cyclic_isr(void);

private:
	PT1 filter_poti1;
	PT1 filter_poti2;
};
	

// Referenzierung des Klassenobjektes daten => siehe DATEN.cpp
extern CONTROLLER controller;

# endif
