`include "RGB_WS2812B_64.v"
// http://verilogtutorial.blogspot.ch/2012/09/verilog-timescale-system-tasks.html
`timescale 10ns/1ns
//
module ICARUS_TB;
	integer file;
	reg clk;
	reg rgb_ext_activ;
	reg [0:191] rgb_data_01;
	reg [0:191] rgb_data_02;
	reg [0:191] rgb_data_03;
	reg [0:191] rgb_data_04;
	reg [0:191] rgb_data_05;
	reg [0:191] rgb_data_06;
	reg [0:191] rgb_data_07;	
	reg [0:191] rgb_data_08;
	wire out;
	
	//
	
	initial 
		begin
			clk <= 1;
			rgb_ext_activ <= 0;
			//
			rgb_data_01   <= 192'b0000_0010;
			rgb_data_02   <= 192'b0000_0010;
			rgb_data_03   <= 192'b0000_0010;
			rgb_data_04   <= 192'b0000_0010;
			rgb_data_05   <= 192'b0000_0010;
			rgb_data_06   <= 192'b0000_0010;
			rgb_data_07   <= 192'b0000_0010;
			rgb_data_08   <= 192'b0000_0010;
			//
			$dumpfile("vcd\\\icarus_tb.vcd"); 
			$dumpvars(0, ICARUS_TB); 		
			#100000 $finish; 
		end 
	//
	always #1 clk <= !clk;
	//
	RGB_WS2812B_64 rgb_ws2812b_64(clk,
	                              rgb_data_01, 
								  rgb_data_02,
								  rgb_data_03,
								  rgb_data_04,
								  rgb_data_05,
								  rgb_data_06,
								  rgb_data_07,
								  rgb_data_08,
								  rgb_ext_activ,
								  out);		
endmodule
/*
cd D:\Dropbox\ABBTS_LABOR_DOZ\PYTHON\SWE\APPLIKATION\RGB_MATRIX\FPGA\FPGA_MAX1000_RGB_MATRIX_02_00\src\RGB\RGB_WS2812B_64
C:\iverilog\bin\iverilog -s ICARUS_TB -o icarus_tb.o ICARUS_TB.v
C:\iverilog\bin\vvp icarus_tb.o
*/