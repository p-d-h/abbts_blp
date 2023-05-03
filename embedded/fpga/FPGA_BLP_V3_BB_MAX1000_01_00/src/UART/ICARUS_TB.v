`include "UART.v"
// http://verilogtutorial.blogspot.ch/2012/09/verilog-timescale-system-tasks.html
`timescale 10ns/1ns
//
module ICARUS_TB;
	integer file;
	reg clk;
	reg rxd;
	wire [255:0] data_out;
	wire data_write_copy;
	wire [7:0] bank;
	//
	
	initial 
		begin
			clk <= 1;
			rxd <= 1;	
			//
			$dumpfile("vcd\\\icarus_tb.vcd"); 
			$dumpvars(0, ICARUS_TB); 
			//
			#90 rxd <= 1;
			//
			// 0x3C => <
			#108 rxd <= 0;// startbit
			#108 rxd <= 1;// bit 0
			#108 rxd <= 0;// bit 1
			#108 rxd <= 1;// bit 2
			#108 rxd <= 0;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 0;// bit 5
			#108 rxd <= 1;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			/*
			#108 rxd <= 0;// startbit
			#108 rxd <= 0;// bit 0
			#108 rxd <= 0;// bit 1
			#108 rxd <= 1;// bit 2
			#108 rxd <= 1;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			*/
			//	
			// BANK 0x30 => 0
			#108 rxd <= 0;// startbit
			#108 rxd <= 0;// bit 0
			#108 rxd <= 0;// bit 1
			#108 rxd <= 0;// bit 2
			#108 rxd <= 0;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			//			
			// 0x31 => 1
			#108 rxd <= 0;// startbit
			#108 rxd <= 1;// bit 0
			#108 rxd <= 0;// bit 1
			#108 rxd <= 0;// bit 2
			#108 rxd <= 0;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			//	
			// Daten 0x32 => 2
			#108 rxd <= 0;// startbit
			#108 rxd <= 0;// bit 0
			#108 rxd <= 1;// bit 1
			#108 rxd <= 0;// bit 2
			#108 rxd <= 0;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			//			
			// 0x30 => 0
			#108 rxd <= 0;// startbit
			#108 rxd <= 0;// bit 0
			#108 rxd <= 0;// bit 1
			#108 rxd <= 0;// bit 2
			#108 rxd <= 0;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			//	
			// 0x3E => >
			#108 rxd <= 0;// startbit
			#108 rxd <= 0;// bit 0
			#108 rxd <= 1;// bit 1
			#108 rxd <= 1;// bit 2
			#108 rxd <= 1;// bit 3
			#108 rxd <= 1;// bit 4
			#108 rxd <= 1;// bit 5
			#108 rxd <= 0;// bit 6
			#108 rxd <= 0;// bit 7
			#108 rxd <= 1;// stopbit
			//	
			#10000 $finish; 
		end 
	//
	always #1 clk <= !clk;
	//
	UART uart(clk, rxd, data_out, data_write_copy, bank);
endmodule
/*
cd D:\Dropbox\ABBTS_LABOR_DOZ\NETZFREQUENZ\QUARTUS\FREQUENZMESSUNG\src\CLOCK\WDT
C:\iverilog\bin\iverilog -s ICARUS_TB -o icarus_tb.o ICARUS_TB.v
C:\iverilog\bin\vvp icarus_tb.o
*/