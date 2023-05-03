#ifndef _oled_h
#define _oled_h

#include <Arduino.h>
#include "main.h"
#include "DATEN.h"
#include "HAL.h"
#include "OLED.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"


#define SCREEN_WIDTH 128 // OLED Breite in Pixel
#define SCREEN_HEIGHT 64 // OLED Höhe in Pixel
#define OLED_RESET     -1 // Reset Pin wird beim verwendeten OLED nicht benötigt => -1

class OLED {
public:
	boolean led1;
    Adafruit_SSD1306 display;

    OLED();
	void setup(void);
	void update(void);
};

extern OLED oled;

#endif