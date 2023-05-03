#ifndef _PT2_H_
#define _PT2_H_

class PT2 {
public:
	float       rX;
	float       rY;
	float       rK;
	float		rT1;
	float		rT2;

    PT2(void);
	PT2(float rK, float rT1, float rT2);
	~PT2(void);
	void setup(void);
	void reset(void);
	float cyclic(float rX);

private:
    float rXX;
};

# endif
