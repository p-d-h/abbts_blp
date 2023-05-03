#ifndef _REGLER_H_
#define _REGLER_H_

#include "dt1.h"

#define CTRL_I 1
#define CTRL_PI 2
#define CTRL_PD 3
#define CTRL_PID 4

class REGLER {
// Grundlegende Reglerstruktur PID-T1-Regler:
// G(jw) = Kr*[1+1/(Tn*jw)+(Tv*jw/(1+Tvz*jw)]  (seriell-parallel)
public:
    // Input
    int         bReset;
    int         bEna_AWU;  // Anti-Windup aktivieren
    int         reglertyp;  // 0: P, 1:I, 2:PI, 3:PDT1, 4:PIDT1
	float       rE;  // Regelfehler
	float       rKr;  // Verstaerkung
	float       rTi;  // Integrationszeit (Tn, Nachstellzeit)
	float       rTd;  // Differentiationszeit (Tv)
	float       rT1;  // T1-Zeitkostante fuer DT1-Verhalten
	float       rYlim_UL;  // oberes Limit Anti-Windup
	float       rYlim_LL;  // unteres Limit Anti-Windup
	float       rY_FF;  // Feed-Forward
	// Output
	int         bAWU_UL_Act;  // oberes Limit aktiv
	int         bAWU_LL_Act;  // unteres Limit aktiv
	float       rY;  // Stellgroesse gesamt
	float       rY_P;  // P-Anteil Stellgroesse
	float       rY_I;  // I-Anteil Stellgroesse
	float       rY_D;  // D-Anteil Stellgroesse

    REGLER(void);  // Konstruktor
    REGLER(int reglertyp, float rKr, float rTi, float rTd, float rT1, int bEna_AWU, float rYlim_UL, float rYlim_LL);  // Konstruktor
	~REGLER(void);  // Destruktor
	void setup(void);
	void reset(void);
	void eval_reglertyp(void);  // Reglertyp auswerten
	// ToDo: weitere Methoden "cyclic" mit zusätzlichen Parametern denkbar
	float cyclic(int bReset, float rE, float rY_FF);
	int get_bAWU_UL_Act(void);
	int get_bAWU_LL_Act(void);
	float get_rY_P(void);
	float get_rY_I(void);
	float get_rY_D(void);

private:
    int bEna_Kr;  // Freigabesignal P-Anteil
	int	bEna_Ti;  // Freigabesignal I-Anteil
	int	bEna_Td;  // Freigabesignal D-Anteil;
	float rIntegralCalc;
	float rYcalc;
    DT1 dt1;  // Objekt der Klasse DT1
};

# endif
