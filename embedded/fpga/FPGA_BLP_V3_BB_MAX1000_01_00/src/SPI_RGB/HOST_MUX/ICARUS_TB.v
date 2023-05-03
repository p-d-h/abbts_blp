`include "HOST_MUX.v"
// http://verilogtutorial.blogspot.ch/2012/09/verilog-timescale-system-tasks.html
`timescale 10ns/1ns
//
module ICARUS_TB;
	// SPI_HOST
	integer file;
	reg clk;
	reg clk_1kHz;
	reg [255:0] data_1;	
	reg [7:0] bank_1;	
	reg data_write_copy_1;
	reg [255:0] data_2;	
	reg [7:0] bank_2;	
	reg data_write_copy_2;
	wire [255:0] data;	
	wire [7:0] bank;	
	wire data_write_copy;
	//
	initial 
		begin
			clk <= 1;		
			clk_1kHz <= 1;		
			bank_1 <= 0;
			data_1 <= 0;
			data_write_copy_1 <= 0;
			bank_2 <= 0;
			data_2 <= 0;
			data_write_copy_2 <= 0;
			//
			$dumpfile("vcd\\\icarus_tb.vcd"); 
			$dumpvars(0, ICARUS_TB); 
			//
			#2 data_write_copy_2 <= 1;
			#2 data_write_copy_2 <= 0;
			//
			#8 bank_1 <= 1;
			#0 data_1 <= 1;
			#2 data_write_copy_1 <= 1;
			#2 data_write_copy_1 <= 0;
			//
			#8 bank_2 <= 2;
			#0 data_2 <= 2;
			#2 data_write_copy_2 <= 1;
			#2 data_write_copy_2 <= 0;
			//
			#20 $finish; 
		end 
	//
	always #1 clk <= !clk;
	always #10 clk_1kHz <= !clk_1kHz;
	//
	HOST_MUX host_mux(clk, 
	                  clk_1kHz,
	                  data_1, 
					  data_write_copy_1, 
					  bank_1, 
					  data_2, 
					  data_write_copy_2, 
					  bank_2, 					 
					  data, 
					  data_write_copy, 
					  bank);
	//
endmodule
//
/*
cd D:\Dropbox\ABBTS_LABOR_DOZ\MOTION_CONTROL\FPGA\QUARTUS\FPGA_MODUL_MAX1000_00_12\src\SPI_FPGA_HOST
C:\iverilog\bin\iverilog -s ICARUS_TB -o icarus_tb.o ICARUS_TB.v
C:\iverilog\bin\vvp icarus_tb.o
*/