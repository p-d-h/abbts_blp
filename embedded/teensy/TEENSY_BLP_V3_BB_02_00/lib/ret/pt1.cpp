#include "ret_const.h"
#include "PT1.h"

PT1::PT1(void) {
}

PT1::PT1(float rK, float rT) {
    this->rX = 0.0;
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
	float min_rT = 0.0001;
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
		if (this->rT > min_rT)
			max_rT = this->rT;
		else
			max_rT = min_rT;
		
		this->rY = this->rY + (-this->rY + this->rK * this->rX) / max_rT * rDt;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
// Zyklische Methode mit Anpassung der Verstaerkung, Verwendung z.B. in der SA-Lueftungsanlage
float PT1::cyclic_rK(float rK, float rX) {
	this->rK = rK;
	float min_rT = 0.0001;
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
		if (this->rT > min_rT)
			max_rT = this->rT;
		else
			max_rT = min_rT;

		this->rY = this->rY + (-this->rY + this->rK * this->rX) / max_rT * rDt;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
// Zyklische Methode mit Anpassung der Zeitkonstanten, Verwendung z.B. im ATM-Unterricht
float PT1::cyclic_rT(float rT, float rX) {
	this->rT = rT;
	float min_rT = 0.0001;
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
		if (this->rT > min_rT)
			max_rT = this->rT;
		else
			max_rT = min_rT;

		this->rY = this->rY + (-this->rY + this->rK * this->rX) / max_rT * rDt;
	}
	else
		this->rY = this->rX;

	return this->rY;
}
