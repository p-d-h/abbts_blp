#ifndef _RET_H_
#define _RET_H_

//#include "pt1.h"
//#include "pt2.h"
#include "dt1.h"
#include "ptt.h"
#include "regler.h"
#include "raum.h"


class RET {
public:
	int bReset;
    int bPraesenz;
    int bFenster;
	float rXin_1;
	float rXin_2;
	float rXin_3;
	float rXin_4;
	float rXin_5;
	float rXin_6;
	float rXin_7;
	float rXin_8;
	float rXin_9;
	float rXin_10;
	float rXout_1;

	RET(void);
	~RET(void);
	void setup(void);
	void reset(void);

private:
    REGLER regler;
};


# endif
