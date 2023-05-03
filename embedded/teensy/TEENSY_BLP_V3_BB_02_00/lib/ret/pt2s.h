#ifndef _PT2S_H_
#define _PT2S_H_

class PT2S {
public:
	float       rX;
	float       rY;
	float       rK;
	float		rD;  // Zeta, Dämpfung
	float		rW0;  // Omega, Eckfrequenz

    PT2S(void);
	PT2S(float rK, float rD, float rW0);
	~PT2S(void);
	void setup(void);
	void reset(void);
	float cyclic(float rX);

private:
    float rXX;
};

# endif
