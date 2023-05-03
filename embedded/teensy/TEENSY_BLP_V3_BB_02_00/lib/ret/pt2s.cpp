#include "ret_const.h"
#include "PT2S.h"

PT2S::PT2S(void) {
}

PT2S::PT2S(float rK, float rD, float rW0) {
    this->rX = 0.0;
	this->rK = rK;
	this->rD = rD;  // Dämpfung [0 .. 1]
	this->rW0 = rW0;  // Eckfrequenz := 1/T > 0.0 rad/s
	this->setup();
	this->reset();
}

PT2S::~PT2S(void) {
}

void PT2S::setup(void) {
	;
}

void PT2S::reset(void) {
    this->rXX = 0.0;
	this->rY = 0.0;
}

float PT2S::cyclic(float rX) {
	float rD_lim;
	float rDy;
	float rDx;

	/*
    rDy := RET_COMMON.rDt*rOmega*rXX;
    rDx := RET_COMMON.rDt*rOmega*(rK*rX - rY - 2*rZeta*rXX);
    rXX := rXX + rDx;
    rY := rY + rDy;
	*/

	this->rX = rX;

    if (this->rW0 > 0.0) {
	    if (this->rD < 0.0) {  // Bereich Dämpfung [0 .. 1] abfangen
	        rD_lim = 0.0;
	    }
	    else {
	        if (this->rD > 1.0) {
	            rD_lim = 1.0;
	        }
	        else {
	            rD_lim = this->rD;
	        }
	    }
        // Berechnung
        rDy = this->rW0 * this->rXX * rDt;
        rDx = this->rW0 * (this->rK * this->rX - this->rY - 2 * rD_lim * this->rXX) * rDt;
        this->rXX = this->rXX + rDx;
        this->rY = this->rY + rDy;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
