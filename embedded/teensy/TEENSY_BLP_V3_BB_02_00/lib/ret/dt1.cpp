#include "ret_const.h"
#include "DT1.h"

DT1::DT1(void) {
}

DT1::DT1(float rTd, float rT1) {
    this->rXin = 0.0;
	this->rTd = rTd;
	this->rT1 = rT1;
	this->setup();
	this->reset();
}

DT1::~DT1(void) {
}

void DT1::setup(void) {
	;
}

void DT1::reset(void) {
    this->rXin_old = 0.0;
    this->rDxe = 0.0;
    this->rDxa = 0.0;
	this->rXout = 0.0;
}

float DT1::cyclic(float rXin) {
	this->rXin = rXin;

	/*
    IF (rTvz > 0.0) THEN
	rDxe := rTv/rTvz*(rE - rEold);
	rEold := rE;
	rDxa := rA/rTvz*RET_COMMON.rDt;
    END_IF
    rA := rA + rDxe - rDxa;
	*/

	if (this->rT1 > 0.0) {
		this->rDxe = this->rTd / this->rT1 * (this->rXin - this->rXin_old);
		this->rXin_old = this->rXin;
		this->rDxa = this->rXout / this->rT1 * rDt;
		this->rXout = this->rXout + this->rDxe - this->rDxa;
	}
	else
		this->rXout = this->rXin;

	return this->rXout;
}
