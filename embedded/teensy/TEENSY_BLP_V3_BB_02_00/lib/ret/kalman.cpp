#include "kalman.h"

KALMAN::KALMAN(void) {
	this->setup();
}


KALMAN::KALMAN(float rQ, float rR) {
	this->rQ = rQ;
	this->rR = rR;
	this->setup();
}

void KALMAN::setup() {
	;
}

void KALMAN::reset() {
	this->X_hat = 0.0;
	this->X_hat_min = 0.0;
	this->poise = 0.0;
	this->Pmin = 0.0;
	this->K = 0.0;

	this->rY = 0.0;
}

float KALMAN::cyclic(float rX) {
	float denominator;

	/*
	K := Pmin/(Pmin + rR);
	X_hat := X_hat_min + K*(rNoisySensor - X_hat_min);
	poise := (1 - K)*Pmin;
	Pmin := poise + rQ;
	X_hat_min := X_hat;
	rSensor := X_hat;
	*/

	this->rX = rX;

	if ((this->Pmin + this->rR) >= 0.001) {
		denominator = (this->Pmin + this->rR);
	} else {
		denominator = 0.001;
	}	
	this->K = this->Pmin / denominator;
	this->X_hat = this->X_hat_min + this->K * (this->rX - this->X_hat_min);
	this->poise = (1.0 - this->K) * this->Pmin;
	this->Pmin = poise + this->rQ;
	this->X_hat_min = this->X_hat;
	this->rY = this->X_hat;

	return this->rY;
}
