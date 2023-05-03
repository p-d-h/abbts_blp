////////////////////////////////////////////////////////////////////////////////////////////
module UART( 
	input CLK,
	input RXD,
	output reg [255:0] DATA_OUT,
	output reg DATA_WRITE_COPY,
	output reg [7:0] BANK
	);
	//
	reg [7:0] byte_ctr;
	reg [7:0] byte_even;
	reg [7:0] byte_odd;
	reg [7:0] byte_even_odd;
	reg [7:0] bit_offset;
	reg uart_frg;
	reg [3:0] write_data;
	//
	wire [7:0] byte_value;
	wire done;
	//
	UART_RXD_BYTE uart_rxd_byte(CLK, RXD, byte_value, done);
	//
	initial
	begin
		DATA_OUT <= 0;
		DATA_WRITE_COPY <= 0;
		BANK <= 0;
		//
		byte_even <= 0;
		byte_odd <= 0;
		byte_even_odd <= 0;
		byte_ctr <= 0;
		bit_offset <= 0;
		uart_frg <= 0;
		write_data <= 0;
	end
	//
	always	@(posedge CLK)
	begin
		if (done)
			begin
			if (byte_value == 8'h3C) /* ascii < */
				begin
				uart_frg <= 1;
				byte_ctr <= 0;
				bit_offset <= 0;
				DATA_OUT <= 0;
				BANK <= 0;
				end
			if (byte_value == 8'h3E) /* ascii > */
				begin
				uart_frg <= 0;
				byte_ctr <= 0;
				DATA_WRITE_COPY <= 1;
				end
			end
		//
		if (DATA_WRITE_COPY) DATA_WRITE_COPY <= 0;
		//
		if (uart_frg && done)
			begin
			if ((byte_ctr % 2) == 0)
				begin
				byte_even <= byte_value;
				byte_ctr <= byte_ctr + 1;
				write_data <= 0;
				end
			else
				begin
				byte_odd <= byte_value;
				write_data <= 1;
				end
			//
			end
		//
		if (write_data == 1)
			begin
			case (byte_even)
				8'h30: byte_even_odd <= 8'h00;// 0
				8'h31: byte_even_odd <= 8'h10;// 1
				8'h32: byte_even_odd <= 8'h20;// 2
				8'h33: byte_even_odd <= 8'h30;// 3
				8'h34: byte_even_odd <= 8'h40;// 4
				8'h35: byte_even_odd <= 8'h50;// 5
				8'h36: byte_even_odd <= 8'h60;// 6
				8'h37: byte_even_odd <= 8'h70;// 7
				8'h38: byte_even_odd <= 8'h80;// 8
				8'h39: byte_even_odd <= 8'h90;// 9
				8'h61: byte_even_odd <= 8'ha0;// a
				8'h62: byte_even_odd <= 8'hb0;// b
				8'h63: byte_even_odd <= 8'hc0;// c
				8'h64: byte_even_odd <= 8'hd0;// d
				8'h65: byte_even_odd <= 8'he0;// e
				8'h66: byte_even_odd <= 8'hf0;// f
				8'h41: byte_even_odd <= 8'ha0;// A
				8'h42: byte_even_odd <= 8'hb0;// B
				8'h43: byte_even_odd <= 8'hc0;// C
				8'h44: byte_even_odd <= 8'hd0;// D
				8'h45: byte_even_odd <= 8'he0;// E
				8'h46: byte_even_odd <= 8'hf0;// F
				default: byte_even_odd <= 8'h00;
			endcase
			write_data <= 2;
			end
		//
		if (write_data == 2)
			begin
			case (byte_odd)
				8'h30: byte_even_odd[3:0] <= 4'h0;// 0
				8'h31: byte_even_odd[3:0] <= 4'h1;// 1
				8'h32: byte_even_odd[3:0] <= 4'h2;// 2
				8'h33: byte_even_odd[3:0] <= 4'h3;// 3
				8'h34: byte_even_odd[3:0] <= 4'h4;// 4
				8'h35: byte_even_odd[3:0] <= 4'h5;// 5
				8'h36: byte_even_odd[3:0] <= 4'h6;// 6
				8'h37: byte_even_odd[3:0] <= 4'h7;// 7
				8'h38: byte_even_odd[3:0] <= 4'h8;// 8
				8'h39: byte_even_odd[3:0] <= 4'h9;// 9
				8'h61: byte_even_odd[3:0] <= 4'ha;// a
				8'h62: byte_even_odd[3:0] <= 4'hb;// b
				8'h63: byte_even_odd[3:0] <= 4'hc;// c
				8'h64: byte_even_odd[3:0] <= 4'hd;// d
				8'h65: byte_even_odd[3:0] <= 4'he;// e
				8'h66: byte_even_odd[3:0] <= 4'hf;// f
				8'h41: byte_even_odd[3:0] <= 4'ha;// A
				8'h42: byte_even_odd[3:0] <= 4'hb;// B
				8'h43: byte_even_odd[3:0] <= 4'hc;// C
				8'h44: byte_even_odd[3:0] <= 4'hd;// D
				8'h45: byte_even_odd[3:0] <= 4'he;// E
				8'h46: byte_even_odd[3:0] <= 4'hf;// F
				default: byte_even_odd <= 8'h00;
			endcase
			write_data <= 3;
			end
		//
		if (write_data == 3)
			begin
			//bit_offset <= bit_offset + 8;
			write_data <= 4;
			end
		//
		if (write_data == 4)
			begin
			if (byte_ctr == 1)
				begin
				BANK <= byte_even_odd;
				end
			else
				begin
				bit_offset <= bit_offset + 8;
				DATA_OUT[bit_offset + 0] <= byte_even_odd[7];
				DATA_OUT[bit_offset + 1] <= byte_even_odd[6];
				DATA_OUT[bit_offset + 2] <= byte_even_odd[5];
				DATA_OUT[bit_offset + 3] <= byte_even_odd[4];
				DATA_OUT[bit_offset + 4] <= byte_even_odd[3];
				DATA_OUT[bit_offset + 5] <= byte_even_odd[2];
				DATA_OUT[bit_offset + 6] <= byte_even_odd[1];	
				DATA_OUT[bit_offset + 7] <= byte_even_odd[0];
				end
			byte_ctr <= byte_ctr + 1;
			write_data <= 0;
			end
		//
	end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////
module UART_RXD_BYTE( 
	input CLK,
	input RXD,
	output reg [7:0] BYTE_VALUE,
	output reg DONE
	);
	//
	reg [7:0] bit_sync_ctr;
	reg [7:0] bit_ctr;
	reg uart_frg;
	reg latch_bit;
	//
	reg hri1, hri2;
	wire imp_start;	
	wire rxd_;
	//
	UART_INP_FILTER uart_inp_filter(CLK, RXD, rxd_); defparam uart_inp_filter.FILTER = 5'd1;
	//
	assign	imp_start = (!hri1 && hri2);
	//
	initial
	begin
		BYTE_VALUE <= 0;
		DONE <= 0;
		//
		bit_sync_ctr <= 0;
		bit_ctr <= 0;
		uart_frg <= 0;
		latch_bit <= 0;
		hri1 <= 0; hri2 <= 0;
	end
	//
	always	@(posedge CLK)
	begin
		hri1 <= rxd_ && !uart_frg;
		hri2 <= hri1;	
		//
		if (imp_start) 
			begin
			uart_frg <= 1;
			bit_sync_ctr <= 78;
			bit_ctr <= 0;
			BYTE_VALUE <= 0;
			end
		//
		if (bit_sync_ctr > 0) bit_sync_ctr <= bit_sync_ctr - 1;
		if ((bit_sync_ctr == 0) && uart_frg)
			begin
			BYTE_VALUE[bit_ctr] <= rxd_;
			bit_ctr <= bit_ctr + 1;
			bit_sync_ctr <= 53;
			latch_bit <= 1;
			end
		else latch_bit <= 0;
		//
		if (bit_ctr == 8)
			begin
			bit_ctr <= 0;
			DONE <= 1;
			uart_frg <= 0;
			end
		else DONE <= 0;
		//

	
	end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////
//	Digitales Filter
module	UART_INP_FILTER (
	input CLK, 
	input IN,
	output reg OUT
	);
//
parameter FILTER = 5'd5;
//
reg [4:0] ctr0;
reg [4:0] ctr1;
//
initial
	begin
	OUT <= 0;
	ctr0 <= 0;
	ctr1 <= 0;
	end
always	@(posedge CLK)
begin
	if (IN && !OUT)
		begin
		ctr0 <= 0;
		ctr1 <= ctr1 + 1;
		end
	//	
	if (!IN && OUT)
		begin
		ctr0 <= ctr0 + 1;
		ctr1 <= 0;
		end	
	//
	if (ctr0 == FILTER)
		begin
		ctr0 <= 0;
		ctr1 <= 0;
		OUT <= 0;
		end
	//
	if (ctr1 == FILTER)
		begin
		ctr0 <= 0;
		ctr1 <= 0;
		OUT <= 1;
		end
	//	
	if (((ctr0 > 0) && IN) || ((ctr1 > 0) && !IN))
		begin
		ctr0 <= 0;
		ctr1 <= 0;
		end	
end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////