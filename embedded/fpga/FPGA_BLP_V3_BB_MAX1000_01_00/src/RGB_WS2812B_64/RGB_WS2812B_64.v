///////////////////////////////////////////////////////////////////////////////
module RGB_WS2812B_64( 
	input CLK,
	input [0:191] RGB_DATA_01,
	input [0:191] RGB_DATA_02,
	input [0:191] RGB_DATA_03,
	input [0:191] RGB_DATA_04,
	input [0:191] RGB_DATA_05,
	input [0:191] RGB_DATA_06,	
	input [0:191] RGB_DATA_07,		
	input [0:191] RGB_DATA_08,
	output wire OUT
	);
	//
	reg	[0:1536] data;// 64 LED zu 24 Bit => 1536 Bit
	reg	[15:0] i;
	reg	[15:0] ctr;
	reg	[1:0] state;
	reg	out_rgb;
	//
	assign OUT = out_rgb;
	//
	initial
	begin
		data <= 0;
		i <= 0;
		ctr <= 1;
		state <= 0;
		out_rgb <= 0;
	end
	//
	always @(posedge CLK)
	begin
	if (state == 0) 
		begin
		ctr <= ctr + 1;
		out_rgb <= 0;
		//
		data[0000:0191] <= RGB_DATA_01[0:191];
		data[0192:0383] <= RGB_DATA_02[0:191];
		data[0384:0575] <= RGB_DATA_03[0:191];
		data[0576:0767] <= RGB_DATA_04[0:191];
		data[0768:0959] <= RGB_DATA_05[0:191];
		data[0960:1151] <= RGB_DATA_06[0:191];
		data[1152:1343] <= RGB_DATA_07[0:191];
		data[1344:1535] <= RGB_DATA_08[0:191];
		data[1536] <= 0;
		//
		if (ctr == 5000) 
			begin
			state <= 1;
			ctr <= 1;
			i <= 0;
			end
		end
		//
	if (state == 1) 
		begin
		if (i == 6144) 
			begin
			state <= 0;
			ctr <= 1;
			i <= 0;
			end
		//
		ctr <= ctr + 1;
		if (ctr == 63) 
			begin
			ctr <= 1;
			i <= i + 1;
			end	
		//
		if (i < 1536)
			begin
			if (data[i] == 1) 
				begin
				//
				if (ctr <= 40)
					out_rgb <= 1;
				else
					out_rgb <= 0;
				//
				end
			else
				begin
				//
				if (ctr <= 20)
					out_rgb <= 1;
				else
					out_rgb <= 0;
				//
				end
			end
		end
	end
endmodule
///////////////////////////////////////////////////////////////////////////////