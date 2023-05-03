#include <math.h>
#include "ret_const.h"
#include "pt2.h"

PT2::PT2(void) {
}

PT2::PT2(float rK, float rT1, float rT2) {
    this->rX = 0.0;
	this->rK = rK;
	this->rT1 = rT1;
	this->rT2 = rT2;
	this->setup();
	this->reset();
}

PT2::~PT2(void) {
}

void PT2::setup(void) {
	;
}

void PT2::reset(void) {
    this->rXX = 0.0;
	this->rY = 0.0;
}

float PT2::cyclic(float rX) {
	float min_rT = 0.0001;
	float max_rT1;
	float max_rT2;
	float rOmega;
	float rZeta;
	float rDy;
	float rDx;

	/*
	// Umrechnung der Faktoren in PT2s
    rOmega := 1/SQRT(MAX(rT1*rT2, 0.001));
    rZeta := rOmega*(rT1+rT2)/2.0;

    IF bReset THEN
        reset();
    END_IF

    rDy := RET_COMMON.rDt*rOmega*rXX;
    rDx := RET_COMMON.rDt*rOmega*(rK*rX - rY - 2*rZeta*rXX);
    rXX := rXX + rDx;
    rY := rY + rDy;
	*/

	this->rX = rX;

	if ((this->rT1 > 0.0) && (this->rT2 > 0.0)) {
		if (this->rT1 > min_rT)
			max_rT1 = this->rT1;
		else
			max_rT1 = min_rT;
		if (this->rT2 > min_rT)
			max_rT2 = this->rT2;
		else
			max_rT2 = min_rT;
		// Umrechnung der Faktoren in PT2s
		rOmega = 1 / sqrt(max_rT1 * max_rT2);
		rZeta = rOmega * (max_rT1 + max_rT2) / 2.0;
        rDy = rOmega * this->rXX * rDt;
        rDx = rOmega * (this->rK * this->rX - this->rY - 2 * rZeta * this->rXX) * rDt;
        this->rXX = this->rXX + rDx;
        this->rY = this->rY + rDy;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
