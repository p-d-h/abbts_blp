#include "ret_const.h"
#include "ptt.h"

PTT::PTT(void) {
}

PTT::PTT(float rK, float rTt) {
    this->rX = 0.0;
	this->rK = rK;
	this->rTt = rTt;  // Totzeit [s]
	this->setup();
	this->reset();
}

PTT::~PTT(void) {
}

void PTT::setup(void) {
	;
}

void PTT::reset(void) {
	this->rY = 0.0;
	ii = 0;
	for (ii = 0; ii<=size_of_array; ii++) {
	        //this->arX[ii] = 0.0;  // mit Eingangswert initialisieren
            this->arX[ii] = this->rX;  // mit Eingangswert initialisieren
        }
}

float PTT::cyclic(float rX) {

	/*
    iN := REAL_TO_INT(rTt/MAX(RET_COMMON.rDt, 0.001));
    iN := LIMIT(1, iN, 5000);
    FOR ii := iN TO 1 BY -1 DO
        arX[ii] := arX[ii - 1];
    END_FOR
    arX[0] := rX;
    rY := rK*arX[iN];
	*/

	this->rX = rX;

    if (this->rTt > 0.0) {
        // Berechnung
        this->iN = this->rTt / rDt;
        if (this->iN < 1) {
            this->iN = 1;
            }
        if (this->iN > size_of_array) {
            this->iN = size_of_array;
            }
        //this->iN = LIMIT(1, this->iN, 5000);
        for (this->ii = this->iN; this->ii >= 1; this->ii--) {
            this->arX[this->ii] = this->arX[this->ii - 1];
        }
        this->arX[0] = rX;
        this->rY = this->rK * this->arX[this->iN];
	}
	else
		this->rY = this->rX;

	return this->rY;
}
