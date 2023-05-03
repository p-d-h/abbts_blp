`include "RGB_PL9823.v"
// http://verilogtutorial.blogspot.ch/2012/09/verilog-timescale-system-tasks.html
`timescale 10ns/1ns
//
module ICARUS_TB;
	integer file;
	reg clk;
	reg [7:0] D1_ROT;
	reg [7:0] D1_GRUEN;
	reg [7:0] D1_BLAU;	
	reg [7:0] D2_ROT;
	reg [7:0] D2_GRUEN;
	reg [7:0] D2_BLAU;	
	reg [7:0] D3_ROT;
	reg [7:0] D3_GRUEN;
	reg [7:0] D3_BLAU;	
	wire out;
	//
	initial 
		begin
			clk <= 1;
			D1_ROT   <= 8'b0000_0001;
			D1_GRUEN <= 8'b0000_0010;
			D1_BLAU  <= 8'b0000_0100;
			D2_ROT   <= 8'b0000_1000;
			D2_GRUEN <= 8'b0000_0000;
			D2_BLAU  <= 8'b0000_0000;
			D3_ROT   <= 8'b0000_0000;
			D3_GRUEN <= 8'b0000_0000;
			D3_BLAU  <= 8'b0000_0000;			
			//
			$dumpfile("vcd\\\icarus_tb.vcd"); 
			$dumpvars(0, ICARUS_TB); 		
			#100000 $finish; 
		end 
	//
	always #1 clk <= !clk;
	//
	RGB_PL9823 rgb_pl9823(clk,
						  D1_ROT,
						  D1_GRUEN,
						  D1_BLAU,
						  D2_ROT,
						  D2_GRUEN,
						  D2_BLAU,
						  D3_ROT,
						  D3_GRUEN,
						  D3_BLAU,
						  out);					
endmodule
/*
cd D:\Dropbox\ABBTS_LABOR_DOZ\MOTION_CONTROL\FPGA\FPGA_IO_MODUL_RGB_MAX1000_00_01\src\RGB
C:\iverilog\bin\iverilog -s ICARUS_TB -o icarus_tb.o ICARUS_TB.v
C:\iverilog\bin\vvp icarus_tb.o
*/