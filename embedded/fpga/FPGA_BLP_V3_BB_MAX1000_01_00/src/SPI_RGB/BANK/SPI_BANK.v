////////////////////////////////////////////////////////////////////////////////////////////
module SPI_BANK_OUT_RGB_64(
	input CLK,
	input [255:0] DATA,
	input COPY,
	input [7:0] BANK,
	output reg [255:0] DATA_00,
	output reg [255:0] DATA_01,
	output reg [255:0] DATA_02,
	output reg [255:0] DATA_03,
	output reg [255:0] DATA_04,
	output reg [255:0] DATA_05,
	output reg [255:0] DATA_06,
	output reg [255:0] DATA_07
	);
	//
	initial
	begin
		DATA_00 <= 0;
		DATA_01 <= 0;
		DATA_02 <= 0;
		DATA_03 <= 0;
		DATA_04 <= 0;
		DATA_05 <= 0;
		DATA_06 <= 0;
		DATA_07 <= 0;
	end
	//
	always @(posedge CLK)
	begin
	if (COPY) 
		begin
		case(BANK)
			00: DATA_00 <= DATA;
			01: DATA_01 <= DATA;
			02: DATA_02 <= DATA;
			03: DATA_03 <= DATA;
			04: DATA_04 <= DATA;
			05: DATA_05 <= DATA;
			06: DATA_06 <= DATA;
			07: DATA_07 <= DATA;
			//default: DATA_ <= DATA;
			endcase
		end
	end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////