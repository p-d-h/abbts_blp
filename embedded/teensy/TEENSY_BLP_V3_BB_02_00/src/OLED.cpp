#include <Arduino.h>
#include "main.h"
#include "DATEN.h"
#include "HAL.h"
#include "OLED.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "CONTROLLER.h"



OLED::OLED() {
  // Wire => Grove Pinout https://wiki.seeedstudio.com/Grove_System/#interface-of-grove-modules
  // Wire1 => Erweiterung ADC DAC
  // Wire2 => OLED Teensy
  oled.display =  Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);
}


void OLED::setup(void){
  String line = "";
  // SSD1306_SWITCHCAPVCC = Spannung aus der 3.3V Spannungsversorgung
  oled.display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // I2C Adresse des Displays 0x3C
  //Wire2.setClock(1000000);
  oled.display.clearDisplay();
  oled.display.setTextColor(WHITE);// setze die Textfarbe auf
  oled.display.setTextSize(2);// Textgrösse 1
  line = "ABB TS"; oled.display.println(line); 
  line = ""; oled.display.println(line);
  line = "BLP V3"; oled.display.println(line);
  oled.display.display();
}

void OLED::update(void) {
  String line = "";

  // put your main code here, to run repeatedly:
  oled.display.clearDisplay();
  oled.display.setTextColor(WHITE);// setze die Textfarbe auf
  oled.display.setTextSize(1);// Textgrösse 1

  oled.display.setCursor(0, 0);// Cursorposition oben links

  line = "BLP V3 TEENSY"; oled.display.println(line); 
  line = ""; oled.display.println(line);
  line = "   UP = " + String(!hal.bSwUp); oled.display.println(line);
  line = " DOWN = " + String(!hal.bSwDown); oled.display.println(line);
  line = " LEFT = " + String(!hal.bSwLeft); oled.display.println(line);
  line = "RIGHT = " + String(!hal.bSwRight); oled.display.println(line);
  line = "   OK = " + String(!hal.bSwOk); oled.display.println(line);
  line = "  1Hz = " + String(!hal.in.bClk1Hz); oled.display.println(line);

  // line = "byIn02 = " + String(hal.fpga.d.byIn02); oled.display.println(line);
  // line = "byOut1 = " + String(hal.teensy.d.byOut01); oled.display.println(line);
  // line = "byOut2 = " + String(hal.teensy.d.byOut02); oled.display.println(line);
  // line = "iIn07 = " + String(hal.fpga.d.iIn07); oled.display.println(line);
  // line = "counter = " + String(counter++); oled.display.println(line);
    
  oled.display.display();

}

OLED oled;