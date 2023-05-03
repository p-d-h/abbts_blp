#ifndef _RAUM_H_
#define _RAUM_H_

#include "pt1.h"
#include "pt2.h"
#include "ptt.h"

class RAUM {
public:
    // Input
    int         bReset;
	float       rY_RT;  // Stellgroesse Regler Temperatur [0 ... 100%]
	// Output
    float       rX_RT;  // Istwert Raumtemperatur
	float       rX_T_ABL;  // Istwert Temperatur ABL
	float       rX_CO2;  // Istwert CO2-Konzentration ppm
	// Physikalische Signale (Input)
	int         bPraesenz_;  // Personen anwesend (1)
	int         bFenster_;  // Fensteroeffnung (0) -> Fenster ist zu
	float       rX_VL_; // Istwert Vorlauftemperatur
	float       rX_T_ZUL_;  // Istwert Temperatur ZUL
	float       rX_T_AUL_;  // Istwert Temperatur AUL
	float       rX_CO2_;  // Istwert CO2 AUL
	float       rX_DD_ZUL_VAV_;  // Istwert Druckdifferenz ZUL mit Einfluss VAV-Klappe
	float       rX_DD_ABL_VAV_;  // Istwert Druckdifferenz ABL mit Einfluss VAV-Klappe
	float       rX_dDD_ZUL_VAV_;  // Istwert Druckdifferenz VAV-Klappe ZUL
	float       rX_dDD_ABL_VAV_;  // Istwert Druckdifferenz VAV-Klappe ABL
	// Physikalische Signale (Output)
	float       rX_DD_ZUL_Raum_;  // Istwert Druckdifferenz Raum, aufgrund ZUL
	float       rX_DD_ABL_Raum_;  // Istwert Druckdifferenz Raum, aufgrund ABL
	float       rX_DD_Raum_;  // Istwert Druckdifferenz Raum (ZUL - ABL)
	float       rX_RT_Senke_;  // Istwert Temperatursenke (Heizquelle im Raum) -> massgebend für thermische Verluste des Raumes
	float       rX_RL_;  // Istwert Temperatur Rücklauf
	float       rX_DD_Fenster_;  // Istwert Druckdifferenz Fensteroeffnung
	float       rX_T_Verluste_Huelle_;  // Thermische Verluste Gebaudehuelle
    RAUM(void);  // Konstruktor
	~RAUM(void);  // Destruktor
	void setup(void);
	void reset(void);
	void cyclic(int bReset, int bPraesenz_, int bFenster_, float rY_RT, float rX_VL_, float rX_T_ZUL_, float rX_T_ABL_,
	            float rX_CO2_, float rX_DD_ZUL_VAV_, float rX_DD_ABL_VAV_, float rX_dDD_ZUL_VAV_, float rX_dDD_ABL_VAV_);
	float get_rX_RT(void);  // Istwert Raumtemperatur
	float get_rX_T_ABL(void);  // Istwert Temperatur ABL
    float get_rX_CO2(void);  // Istwert CO2-Konzentration ppm
    float get_rX_RL_(void);  // Istwert Temperatur Rücklauf
    float get_rX_DD_Fenster_(void);  // Istwert Druckdifferenz Fensteroeffnung
private:
    int         bEinfluss_T_ZUL_RT_;  // Einfluss Temperatur ZUL auf die Raumtemperatur freischalten
    int         bEinfluss_Fenster_RT_;  // Einfluss Fensteroeffnung auf die Raumtemperatur freischalten
    int         bEinfluss_Fenster_DD_ZUL_;  // Einfluss Fensteroeffnung auf die Druckdifferenz ZUL freischalten
    // Modelle
    PT2 rs_T_RL_pt2;
    PT1 rs_T_Senke_pt1;
    PT2 rs_T_Raum_pt2;
    PTT rs_T_Raum_ptt;
    PT2 rs_T_Losses_pt2;
    PT1 rs_T_ZUL_RT_pt1;
    PT2 rs_CO2_Zunahme_Raum_pt2;
    PTT rs_CO2_Zunahme_Raum_ptt;
    PT2 rs_CO2_Abnahme_Raum_pt2;
    PT2 rs_T_RT_Praesenz_pt2;
    // Modelle zur Fensteroeffnung
    PT1 rs_Fenster_DD_pt1;
    PT2 rs_Fenster_RT_pt2;
    PT2 rs_Fenster_CO2_pt2;
};

# endif
