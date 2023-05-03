#include "ret_const.h"
#include "regler.h"
#include "dt1.h"

REGLER::REGLER(void) {
	// Objekt mit konkreten Parametern instanziieren
	this->bEna_AWU = 1;
	this->rYlim_UL = 100.0;
	this->rYlim_LL = 0.0;
	this->reglertyp = 2;
	this->rKr = 1.0;
	this->rTi = 1.0;
	this->rTd = 0.1;
	this->rT1 = 0.01;
	this->dt1 = DT1(this->rTd, this->rT1);  // DT1
	this->eval_reglertyp();
	this->setup();
	this->reset();
}

REGLER::~REGLER(void) {
    ;
}

REGLER::REGLER(int reglertyp, float rKr, float rTi, float rTd, float rT1, int bEna_AWU, float rYlim_UL, float rYlim_LL) {
	// Objekt mit konkreten Parametern instanziieren
	this->bEna_AWU = bEna_AWU;
	this->rYlim_UL = rYlim_UL;
	this->rYlim_LL = rYlim_LL;
	this->reglertyp = reglertyp;
	this->rKr = rKr;
	this->rTi = rTi;
	this->rTd = rTd;
	this->rT1 = rT1;
	this->dt1 = DT1(this->rTd, this->rT1);  // DT1
	this->eval_reglertyp();
	this->setup();
	this->reset();
}

void REGLER::setup(void) {
	;
}

void REGLER::reset(void) {
    this->rY = 0.0;
    this->rY_P = 0.0;
    this->rY_I = 0.0;
    this->rIntegralCalc = 0.0;
    this->rYcalc = 0.0;
    this->rY_D = 0.0;
    this->dt1.reset();
    }

void REGLER::eval_reglertyp(void) {
    this->bEna_Kr = 1;
    if (this->reglertyp == CTRL_I) {
        this->bEna_Kr = 0;
        this->bEna_Ti = 1;
        this->bEna_Td = 0;
    } else if (this->reglertyp == CTRL_PI) {
        this->bEna_Ti = 1;
        this->bEna_Td = 0;
    } else if (this->reglertyp == CTRL_PD) {
        this->bEna_Ti = 0;
        this->bEna_Td = 1;
    } else if (this->reglertyp == CTRL_PID) {
        this->bEna_Ti = 1;
        this->bEna_Td = 1;
    }
}

float REGLER::cyclic(int bReset, float rE, float rY_FF) {
    // Eingangssignale
	this->bReset = bReset;  // Resetieren
	this->rE = rE;
	this->rY_FF = rY_FF;

	// Hilfsvariablen -> siehe CFC-Darstellung
	float min_rT = 0.0001;

    if (this->bReset == 1) {
        this->reset();
    }
    else {  // Regler
        // P-Anteil
        if (this->bEna_Kr == 1) {
            this->rY_P = this->rKr * this->rE;
        } else {
            this->rY_P = 0.0;
            this->rKr = 1.0;  // muss gesetzt werden, da sonst I-Anteil bei reinem I-Regler, aufgrund Struktur, nicht funktioniert
        }
        // I-Anteil
        if (this->bEna_Ti == 1) {
            // Avoid Zero-Division
            if (this->rTi < min_rT) {
                this->rTi = min_rT;
            }
            this->rIntegralCalc = this->rKr * (this->rE * rDt) / this->rTi;
        } else {
            this->rY_I = 0.0;
        }
        // Auswertung Anti-Windup
        if ((this->rY_I + this->rY_FF) >= (this->rYlim_UL - this->rY_FF) && (this->rE > 0.0) && (this->bEna_AWU == 1)) {
            this->rY_I = this->rY_I;
        } else if ((this->rY_I + this->rY_FF) <= (this->rYlim_LL + this->rY_FF) && (this->rE < 0.0) && (this->bEna_AWU == 1)) {
            this->rY_I = this->rY_I;
        } else {
            this->rY_I = this->rY_I + this->rIntegralCalc;
        }
        // DT1-Anteil
        if (this->bEna_Td == 1) {
            this->rY_D = this->dt1.cyclic(this->rKr * this->rE);  // <- hier Objekt integrieren
        } else {
            this->rY_D = 0.0;
        }
        // Addition aller drei Teilkomponenten (P,I und DT1-Anteil)
        // Die Implementation der Begrenzung (Anti-WindUp) entspricht der Umsetzung von BORIS, d.h. solange die Summe
        // der beiden Anteile (P + I) ausserhalb der Limits sind wird das entsprechende Limit + D-Anteil als
        // Stellgrösse ausgegeben -> siehe nachfolgende Zeilen. Ansonsten werden sämtliche drei Anteile (P + I + D)
        // addiert.
        if (((this->rY_P + this->rY_I + this->rY_FF) >= (this->rYlim_UL - this->rY_FF)) && (this->bEna_AWU == 1)) {
            this->rYcalc = this->rYlim_UL + this->rY_D;
        } else if (((this->rY_P + this->rY_I + this->rY_FF) <= (this->rYlim_LL + this->rY_FF)) && (this->bEna_AWU == 1)) {
            this->rYcalc = this->rYlim_LL + this->rY_D;
        } else {
            this->rYcalc = this->rY_P + this->rY_I + this->rY_FF + this->rY_D;
        }
        // Auswertung Anti-Windup
        if (this->bEna_AWU == 1) {
            if ((this->rYcalc <= this->rYlim_UL) && (this->rYcalc >= this->rYlim_LL)) {
                this->bAWU_UL_Act = 0;
                this->bAWU_LL_Act = 0;
            } else if (this->rYcalc > this->rYlim_UL) {
                this->bAWU_UL_Act = 1;
                this->bAWU_LL_Act = 0;
            } else if (this->rYcalc < this->rYlim_LL) {
                this->bAWU_UL_Act = 0;
                this->bAWU_LL_Act = 1;
            }
            if ((this->rYcalc >= this->rYlim_LL) && (this->rYcalc <= this->rYlim_UL)) {
                this->rY = this->rYcalc;
            } else if (this->rYcalc < this->rYlim_LL) {
                this->rY = this->rYlim_LL;
            } else if (this->rYcalc > this->rYlim_UL) {
                this->rY = this->rYlim_UL;
            }
        } else {
            this->rY = this->rYcalc;
            this->bAWU_UL_Act = 0;
            this->bAWU_LL_Act = 0;
        }
    }
    return this->rY;
}

// getter Funktionen
int REGLER::get_bAWU_UL_Act(void) {return this->bAWU_UL_Act;}
int REGLER::get_bAWU_LL_Act(void) {return this->bAWU_LL_Act;}
float REGLER::get_rY_P(void) {return this->rY_P;}
float REGLER::get_rY_I(void) {return this->rY_I;}
float REGLER::get_rY_D(void) {return this->rY_D;}
