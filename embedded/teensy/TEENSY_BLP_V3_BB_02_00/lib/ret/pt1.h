#ifndef _PT1_H_
#define _PT1_H_

class PT1 {
public:
	float       rX;
	float       rY;
	float       rK;
	float		rT;

    PT1(void);
	PT1(float rK, float rT);
	~PT1(void);
	void setup(void);
	void reset(void);
	float cyclic(float rX);
	float cyclic_rK(float rK, float rX);
	float cyclic_rT(float rT, float rX);

private:
    ;
};

# endif
