#include <Arduino.h>
#include "main.h"
#include "DATEN.h"
#include "HAL.h"
#include "OLED.h"
#include <SPI.h>
#include "CONTROLLER.h"
#include "EEPrint.h"

// https://www.pjrc.com/teensy/td_timing_IntervalTimer.html
// siehe auch https://github.com/luni64/TeensyTimerTool
IntervalTimer timer_io_expander;

byte toggle = 0;
byte enable_loop = 0;

void setup() {
	hal.setup();
	oled.setup();
	setup_timer();
	enable_loop = 1;
	// Serial7.println("\n\nsetup succesful\n\n");
}

void loop() {
	/*
	hal.input();
	// hal.modbus_rtu();
	// oled.update();
	controller.cyclic();
	hal.output();
	delay(100);	
	*/

	if(enable_loop == 1){
		toggle = !toggle;
		if(toggle == 1){
			hal.output_isr();
			controller.cyclic_isr();
			hal.spi_fpga_transfer_isr();
			hal.input_isr();
		}else{
			hal.can();
		}
	}

	//digitalWrite(A0, HIGH);
	hal.extension_adc_dac();// Analogerweiterung
	//digitalWrite(A0, LOW);

	delayMicroseconds(50);
}

void timer_io_expander_isr(void) {
	hal.spi_io_expander_input_isr();
	hal.spi_io_expander_output_isr();
}

void timer_eep_isr(void) {
	//digitalWrite(A0, HIGH);
	hal.extension_adc_dac();// Analogerweiterung
	//digitalWrite(A0, LOW);
}

void setup_timer(void) {
	timer_io_expander.begin(timer_io_expander_isr, 1000);// us
	timer_io_expander.priority(0);
}