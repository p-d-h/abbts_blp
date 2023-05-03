module RGB_PL9823( 
	input CLK,
	input [7:0] D1_R,
	input [7:0] D1_G,
	input [7:0] D1_B,
	input [7:0] D2_R,
	input [7:0] D2_G,
	input [7:0] D2_B,
	input [7:0] D3_R,
	input [7:0] D3_G,
	input [7:0] D3_B,
	input [7:0] D4_R,
	input [7:0] D4_G,
	input [7:0] D4_B,
	input [7:0] D5_R,
	input [7:0] D5_G,
	input [7:0] D5_B,
	input [7:0] D6_R,
	input [7:0] D6_G,
	input [7:0] D6_B,
	input [7:0] D7_R,
	input [7:0] D7_G,
	input [7:0] D7_B,
	input [7:0] D8_R,
	input [7:0] D8_G,
	input [7:0] D8_B,
	output reg OUT,
	output OUT_NEG
	);
	//
	reg [0:200] data;
	reg [7:0] i;
	reg [13:0] ctr;
	reg state;
	//
	localparam TRANSFER = 1'd0;
	localparam AUSGABE = 1'd1;	
	//
	assign OUT_NEG = !OUT;
	//
	initial
	begin
		OUT <= 0;
		//
		data <= 0;
		i <= 0;
		ctr <= 1;
		state <= TRANSFER;
	end
	//
	always @(posedge CLK) /* 50MHz => 20ns */
	begin
	if (state == TRANSFER) 
		begin
		ctr <= ctr + 1;
		OUT <= 0;
		/*
		data[000:007] <= 8'b0000_0001;
		data[024:031] <= 8'b0000_0001;
		data[048:055] <= 8'b0000_0001;
		data[072:079] <= 8'b0000_0001;
		data[096:103] <= 8'b0000_0001;
		data[120:127] <= 8'b0000_0001;
		data[144:151] <= 8'b0000_0001;
		data[168:175] <= 8'b0000_0001;
		*/
		
		//
		data[000:007] <= D1_G[7:0];
		data[008:015] <= D1_R[7:0];
		data[016:023] <= D1_B[7:0];
		//
		data[024:031] <= D2_G[7:0];
		data[032:039] <= D2_R[7:0];
		data[040:047] <= D2_B[7:0];
		//
		data[048:055] <= D3_G[7:0];
		data[056:063] <= D3_R[7:0];
		data[064:071] <= D3_B[7:0];
		//
		data[072:079] <= D4_G[7:0];
		data[080:087] <= D4_R[7:0];
		data[088:095] <= D4_B[7:0];
		//
		data[096:103] <= D5_G[7:0];
		data[104:111] <= D5_R[7:0];
		data[112:119] <= D5_B[7:0];
		//
		data[120:127] <= D6_G[7:0];
		data[128:135] <= D6_R[7:0];
		data[136:143] <= D6_B[7:0];
		//
		data[144:151] <= D7_G[7:0];
		data[152:159] <= D7_R[7:0];
		data[160:167] <= D7_B[7:0];
		//
		data[168:175] <= D8_G[7:0];
		data[176:183] <= D8_R[7:0];
		data[184:191] <= D8_B[7:0];		
		//
		data[200] <= 0;
		//
		if (ctr == 5000) /* 3000 * 20ns = 60000ns */
			begin
			state <= AUSGABE;
			ctr <= 1;
			i <= 0;
			end
		end
	//
	if (state == AUSGABE) 
		begin
		if (i == 200) 
			begin
			state <= TRANSFER;
			ctr <= 1;
			i <= 0;
			end
		//
		ctr <= ctr + 1;
		if (ctr == 62) /* 86 * 20ns = 1720ns */
			begin
				ctr <= 1;
				i <= i + 1;
			end	
		//
		if (i < 200)
			begin
			if (data[i] == 1) 
				begin
				//
				if (ctr <= 31) /* 68 * 20ns = 1360ns */
					OUT <= 1;
				else
					OUT <= 0;
				//
				end
			else
				begin
				//
				if (ctr <= 16) /* 18 * 20ns = 360ns */
					OUT <= 1;
				else
					OUT <= 0;
				//
				end
			end
		end
	//
	end
endmodule