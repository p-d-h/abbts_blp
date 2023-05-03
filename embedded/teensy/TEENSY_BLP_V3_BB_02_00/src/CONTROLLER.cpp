#include <Arduino.h>
#include <SPI.h>
#include "CONTROLLER.h"
#include "DATEN.h"
#include <ret.h>
#include "pt2.h"

CONTROLLER::CONTROLLER(void) {
	this->filter_poti1 = PT1(1.0, 0.05);
	this->filter_poti2 = PT1(1.0, 0.05);
	this->setup();
}

CONTROLLER::~CONTROLLER(void) {
}

void CONTROLLER::setup(void) {
	;
}

void CONTROLLER::reset(void) {
	;
}

void CONTROLLER::cyclic(void) {
	//Serial8.println("HALLO");
	//Serial1.print(hal.out.RAUM1_rX_CO2); Serial1.println(" RAUM1_rX_CO2 ");
}

void CONTROLLER::cyclic_isr(void) {
	this->poti1_out = (uint16_t)(this->filter_poti1.cyclic((float)this->poti1_in));
	this->poti2_out = (uint16_t)(this->filter_poti2.cyclic((float)this->poti2_in));
}

CONTROLLER controller;

