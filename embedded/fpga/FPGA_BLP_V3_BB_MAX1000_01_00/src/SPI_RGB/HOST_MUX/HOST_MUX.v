////////////////////////////////////////////////////////////////////////////////////////////
module HOST_MUX (
	input CLK,
	input CLK_1kHz,
	input [255:0] DATA_1,
	input DATA_WRITE_COPY_1,
	input [7:0] BANK_1,
	input [255:0] DATA_2,
	input DATA_WRITE_COPY_2,
	input [7:0] BANK_2,
	output reg [255:0] DATA,
	output reg DATA_WRITE_COPY,
	output reg [7:0] BANK
	);
	//
	reg [15:0] counter;
	reg hri1; reg hri2; reg hri3; reg hri4; reg hri5; reg hri6;
	//
	parameter MUX_DELAY = 16'd1000;
	// Glue Logic
	assign copy_1_re = hri1 && !hri2;
	assign copy_1_fe = !hri1 && hri2;
	assign copy_2_re = hri3 && !hri4;
	assign copy_2_fe = !hri3 && hri4;
	assign clk_1kHz_re = hri5 && !hri6;
	assign clk_1kHz_fe = !hri5 && hri6;
	//	
	initial
	begin
		DATA_WRITE_COPY <= 0;
		BANK <= 0;
		DATA <= 0;	
		//
		counter <= 0;
		hri1 <= 0; hri2 <= 0; hri3 <= 0; hri4 <= 0; hri5 <= 0; hri6 <= 0;
	end	
	//
	always	@(posedge CLK)
	begin
	//
	hri1 <= DATA_WRITE_COPY_1;
	hri2 <= hri1;			
	hri3 <= DATA_WRITE_COPY_2;
	hri4 <= hri3;	
	hri5 <= CLK_1kHz;
	hri6 <= hri5;	
	//
	if (DATA_WRITE_COPY)
		DATA_WRITE_COPY <= 0;
	//
	if (clk_1kHz_re && (counter > 0))
		counter <= counter - 1;
	//
	if (copy_1_re && (counter == 0))
		begin
		DATA <= DATA_1;
		BANK <= BANK_1;
		end
	if (copy_1_fe && (counter == 0))
		DATA_WRITE_COPY <= 1;
	//
	if (copy_2_re)
		begin
		counter <= MUX_DELAY;
		DATA <= DATA_2;
		BANK <= BANK_2;
		end
	if (copy_2_fe)
		DATA_WRITE_COPY <= 1;
	//
end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////