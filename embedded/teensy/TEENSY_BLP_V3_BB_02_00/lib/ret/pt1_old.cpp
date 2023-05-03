#include "ret_const.h"
#include "pt1.h"

PT1::PT1(void) {
}

PT1::PT1(float rK, float rT) {
	this->rK = rK;
	this->rT = rT;
	this->setup();
}

PT1::~PT1(void) {
}

void PT1::setup(void) {
	;
}

void PT1::reset(void) {
	this->rY = 0.0;
}

float PT1::cyclic(float rX) {
	float max_rT;

	/*
	IF (rT > 0.0) THEN
		rY := rY + (-rY + rK*rX)/MAX(rT,0.001)*RET_COMMON.rDt;
	ELSE
		rY := rX;
	END_IF
	*/

	this->rX = rX;

	if (this->rT > 0.0) {
		if (this->rT > 0.0)
			max_rT = this->rT;
		else
			max_rT = 0.0001;
		
		this->rY = this->rY + (-this->rY + this->rK * this->rX) / max_rT * rDt;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
