#include "ret_const.h"
#include "raum.h"
#include "pt1.h"
#include "pt2.h"
#include "ptt.h"
/*
Offene Punkte:
- Ablufttemperatur ohne Einfluss der Raumtemperatur und Klappenstellung
*/

RAUM::RAUM(void) {
	// Objekt mit konkreten Parametern instanziieren
	// Parameter aus CodeSys-Projekt
	this->bEinfluss_T_ZUL_RT_ = 1;
	this->bEinfluss_Fenster_RT_ = 1;
	this->bEinfluss_Fenster_DD_ZUL_ = 1;
	this->rs_T_RL_pt2 = PT2(0.9, 10.0, 30.0);
	this->rs_T_Senke_pt1 = PT1(1.0, 10.0);
	this->rs_T_Raum_pt2 = PT2(1.0, 20.0, 150.0);
	this->rs_T_Raum_ptt = PTT(1.0, 3.0);
    this->rs_T_Losses_pt2 = PT2(0.1, 10.0, 30.0);
    this->rs_T_ZUL_RT_pt1 = PT1(0.2, 30.0);
    this->rs_CO2_Zunahme_Raum_pt2 = PT2(1000.0, 50.0, 50.0);
    this->rs_CO2_Zunahme_Raum_ptt = PTT(1.0, 10.0);
    this->rs_CO2_Abnahme_Raum_pt2 = PT2(1000.0, 20.0, 20.0);
    this->rs_T_RT_Praesenz_pt2 = PT2(1.0, 20.0, 50.0);
    this->rs_Fenster_DD_pt1 = PT1(1.0, 1.0);
    this->rs_Fenster_RT_pt2 = PT2(0.1, 2.0, 5.0);
    this->rs_Fenster_CO2_pt2 = PT2(0.5, 10.0, 20.0);
	this->bReset = 0;
	this->setup();
	this->reset();
}

RAUM::~RAUM(void) {
    ;
}

void RAUM::setup(void) {
	;
}

void RAUM::reset(void) {
    this->rs_T_RL_pt2.reset();
	this->rs_T_Senke_pt1.reset();
	this->rs_T_Raum_pt2.reset();
	this->rs_T_Raum_ptt.reset();
    this->rs_T_Losses_pt2.reset();
    this->rs_T_ZUL_RT_pt1.reset();
    this->rs_CO2_Zunahme_Raum_pt2.reset();
    this->rs_CO2_Zunahme_Raum_ptt.reset();
    this->rs_CO2_Abnahme_Raum_pt2.reset();
    this->rs_T_RT_Praesenz_pt2.reset();
    this->rs_Fenster_DD_pt1.reset();
    this->rs_Fenster_RT_pt2.reset();
    this->rs_Fenster_CO2_pt2.reset();
    // anpassen
    this->rY_RT = 0.0;
	this->rX_RT = 0.0;
	this->rX_T_ABL = 0.0;
    this->rX_CO2 = 0.0;
    this->bPraesenz_ = 0;
    this->bFenster_ = 0;
    this->rX_VL_ = 0.0;
	this->rX_T_ZUL_ = 0.0;
	this->rX_T_AUL_ = 0.0;
	this->rX_CO2_ = 0.0;
	this->rX_DD_ZUL_VAV_ = 0.0;
	this->rX_DD_ABL_VAV_ = 0.0;
	this->rX_dDD_ZUL_VAV_ = 0.0;
	this->rX_dDD_ABL_VAV_ = 0.0;
	// Physikalische Signale (Output)
	this->rX_DD_ZUL_Raum_ = 0.0;
	this->rX_DD_ABL_Raum_ = 0.0;
	this->rX_DD_Raum_ = 0.0;
	this->rX_RT_Senke_ = 0.0;
	this->rX_RL_ = 0.0;
	this->rX_DD_Fenster_ = 0.0;
	this->rX_T_Verluste_Huelle_ = 0.0;
}

void RAUM::cyclic(int bReset, int bPraesenz_, int bFenster_, float rY_RT, float rX_VL_, float rX_T_ZUL_,
                             float rX_T_AUL_, float rX_CO2_, float rX_DD_ZUL_VAV_, float rX_DD_ABL_VAV_,
                             float rX_dDD_ZUL_VAV_, float rX_dDD_ABL_VAV_) {
    // Eingangssignale
	this->bReset = bReset;  // Resetieren
	this->rY_RT = rY_RT;
	this->bPraesenz_ = bPraesenz_;
	this->bFenster_ = bFenster_;
    this->rX_VL_ = rX_VL_;
    this->rX_T_ZUL_ = rX_T_ZUL_;
    this->rX_T_AUL_ = rX_T_AUL_;
    this->rX_CO2_ = rX_CO2_;
    this->rX_DD_ZUL_VAV_ = rX_DD_ZUL_VAV_;
    this->rX_DD_ABL_VAV_ = rX_DD_ABL_VAV_;
    this->rX_dDD_ZUL_VAV_ = rX_dDD_ZUL_VAV_;
    this->rX_dDD_ABL_VAV_ = rX_dDD_ABL_VAV_;
	// Hilfsvariablen -> siehe CFC-Darstellung
	float a1_Praesenz;
	float a1_T_ZUL;
	float a1_T_RL;
	float a1_DD_ZUL_Raum_;
	float a1_T_Raum_;
	float a1_Einfluss_T_ZUL_RT_;
	float a1_total;
	float a1_CO2_Zunahme;
	float a1_CO2_Abnahme;
	float a1_CO2_Abnahme_1;
	float a1_CO2_Abnahme_2;
	int b1_CO2_GE;

    if (this->bReset == 1) {
        this->reset();
    }
    else {
        if (this->bPraesenz_ == 1) {
            a1_Praesenz = this->rs_T_RT_Praesenz_pt2.cyclic(2.0);
        }
        else {
            a1_Praesenz = 0.0;
        }
        a1_T_RL = this->rs_T_RL_pt2.cyclic(this->rX_T_ZUL_);
        a1_DD_ZUL_Raum_ = 0.01 * this->rX_DD_ZUL_Raum_;
        // Thermische Senke
        this->rX_RT_Senke_ = 0.01 * this->rs_T_Senke_pt1.cyclic(this->rX_VL_) * this->rY_RT;
        a1_T_Raum_ = this->rs_T_Raum_ptt.cyclic(this->rs_T_Raum_pt2.cyclic(this->rX_RT_Senke_));
        // Thermische Verluste Gebaudehuelle
        this->rX_T_Verluste_Huelle_ = this->rs_T_Losses_pt2.cyclic(this->rX_RT_Senke_ - this->rX_T_AUL_);
        // Einfluss Temperatur ZUL, Raumtemperatur
        if (this->bEinfluss_T_ZUL_RT_ == 1) {
            a1_Einfluss_T_ZUL_RT_ = this->rX_T_ZUL_ - (a1_T_Raum_ - this->rX_T_Verluste_Huelle_);
            a1_T_ZUL = this->rs_T_ZUL_RT_pt1.cyclic_rK(a1_DD_ZUL_Raum_, a1_Einfluss_T_ZUL_RT_);
        } else {
            a1_Einfluss_T_ZUL_RT_ = 0.0;
            a1_T_ZUL = 0.0;
            this->rs_T_ZUL_RT_pt1.reset();
        }
        a1_total = a1_Praesenz + a1_T_ZUL + (a1_T_Raum_ - this->rX_T_Verluste_Huelle_);
        if (this->bEinfluss_Fenster_RT_ == 1) {
            if (this->bFenster_ == 1) {
                this->rX_RT = a1_total - this->rs_Fenster_RT_pt2.cyclic(a1_total - this->rX_T_AUL_);
            } else {
                this->rX_RT = a1_total;
            }
        } else {
            this->rX_RT = a1_total;
        }
        // MAX rX_T_ABL
        if (a1_T_RL >= this->rX_RT) {
            this->rX_T_ABL = a1_T_RL;
        } else {
            this->rX_T_ABL = this->rX_RT;
        }
        // MAX rX_RL_
        if (this->rX_T_Verluste_Huelle_ >= this->rX_RT) {
            this->rX_RL_ = this->rX_T_Verluste_Huelle_;
        } else {
            this->rX_RL_ = this->rX_RT;
        }
        // Druckdifferenz Raum
        this->rX_DD_ZUL_Raum_ = this->rX_DD_ZUL_VAV_ - this->rX_dDD_ZUL_VAV_;
        this->rX_DD_ABL_Raum_ = this->rX_DD_ABL_VAV_ - this->rX_dDD_ABL_VAV_;
        this->rX_DD_Raum_ = this->rX_DD_ZUL_Raum_ - this->rX_DD_ABL_Raum_;
        // Druckabfall Fensteroeffnung
        if (this->bEinfluss_Fenster_DD_ZUL_ == 1 && this->bFenster_ == 1) {
            this->rX_DD_Fenster_ = this->rs_Fenster_DD_pt1.cyclic(0.2 / 2.0 * (this->rX_DD_ZUL_Raum_ + this->rX_DD_ABL_Raum_));
        } else {
            this->rX_DD_Fenster_ = this->rs_Fenster_DD_pt1.cyclic(0.0);
        }
        // CO2-RS
        if (this->bPraesenz_ == 1) {
            a1_CO2_Zunahme = this->rX_CO2_ + this->rs_CO2_Zunahme_Raum_pt2.cyclic(this->rs_CO2_Zunahme_Raum_ptt.cyclic(1.0));
        } else {
            a1_CO2_Zunahme = this->rX_CO2_ + this->rs_CO2_Zunahme_Raum_pt2.cyclic(this->rs_CO2_Zunahme_Raum_ptt.cyclic(0.0));
        }
        // Vermeidung kleinere CO2-Werte im Raum als in der AUL
        if (this->rX_CO2_ >= this->rX_CO2) {
            b1_CO2_GE = 1;
        } else {
            b1_CO2_GE = 0;
        }
        // CO2-Abnahme wird unterdrückt, falls CO2-Wert im Innern den Wert der AUL unterschreitet
        if (b1_CO2_GE == 0) {
            a1_CO2_Abnahme_1 = this->rs_CO2_Abnahme_Raum_pt2.cyclic(this->rX_DD_ZUL_Raum_ / 100.0);
            if (this->bFenster_ == 1) {  // Fenster ist offen
                a1_CO2_Abnahme_2 = this->rs_Fenster_CO2_pt2.cyclic(this->rX_CO2 - this->rX_CO2_);
            } else {  // Fenster ist zu
                a1_CO2_Abnahme_2 = this->rs_Fenster_CO2_pt2.cyclic(0.0);
            }
        } else {
            a1_CO2_Abnahme_1 = this->rs_CO2_Abnahme_Raum_pt2.cyclic(0.0);
            a1_CO2_Abnahme_2 = this->rs_Fenster_CO2_pt2.cyclic(0.0);
        }
        a1_CO2_Abnahme = a1_CO2_Abnahme_1 + a1_CO2_Abnahme_2;
        this->rX_CO2 = a1_CO2_Zunahme - a1_CO2_Abnahme;

    }
}
// getter Funktionen
float RAUM::get_rX_RT(void) {return this->rX_RT;}
//float RAUM::get_rX_RT(void) {return this->rX_RT_Senke_;}
float RAUM::get_rX_T_ABL(void) {return this->rX_T_ABL;}
float RAUM::get_rX_CO2(void) {return this->rX_CO2;}
float RAUM::get_rX_RL_(void) {return this->rX_RL_;}
float RAUM::get_rX_DD_Fenster_(void) {return this->rX_DD_Fenster_;}
