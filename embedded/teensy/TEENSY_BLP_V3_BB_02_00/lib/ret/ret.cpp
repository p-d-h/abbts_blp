#include "ret_const.h"
#include "ret.h"
#include "pt1.h"
#include "pt2.h"
#include "ptt.h"
#include "dt1.h"
#include "regler.h"
#include "raum.h"

// Konstruktor
RET::RET(void) {
    this->regler = REGLER(2, 5, 2.0, 1.0, 0.1, 1, 100.0, 0.0);
	this->setup();
	this->reset();
}

// Destruktor
RET::~RET(void) {
    ;
}

void RET::setup(void) {
	;
}

void RET::reset(void) {
	;
}
