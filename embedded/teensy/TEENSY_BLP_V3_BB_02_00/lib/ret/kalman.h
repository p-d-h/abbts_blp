#ifndef _KALMAN_H_
#define _KALMAN_H_

class KALMAN {
public:
	float       rX;
	float       rY;
	float       rQ;
	float		rR;

	KALMAN(void);
	KALMAN(float rQ, float rR);
	void setup(void);
	void reset(void);
	float cyclic(float rX);

private:
	// ToDo: Benennung der Variablen optimieren
	float X_hat;
	float X_hat_min;
	float poise;
	float Pmin;
	float K;
};

# endif
