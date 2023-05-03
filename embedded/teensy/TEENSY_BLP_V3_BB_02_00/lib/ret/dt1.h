#ifndef _DT1_H_
#define _DT1_H_

class DT1 {
public:
	float       rXin;
	float       rXout;
	float       rTd;
	float		rT1;

    DT1(void);
	DT1(float rTd, float rT1);
	~DT1(void);
	void setup(void);
	void reset(void);
	float cyclic(float rXin);

private:
    float rXin_old;
    float rDxe;
    float rDxa;
};

# endif
