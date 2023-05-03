////////////////////////////////////////////////////////////////////////////////////////////
module SPI_HOST_RGB (
	input CLK,
	input SPI_CS,
	input SPI_CLK,
	input SPI_MOSI,
	output reg [255:0] DATA_OUT,
	output reg DATA_WRITE_COPY,
	output reg [7:0] BANK
	);
	//
	reg [0:7] cmd_temp;// LSB
	reg [0:7] bank_temp;// LSB	
	reg [255:0] data_out_temp;		
	reg [11:0] spi_clk_ctr;
	reg [11:0] i_cmd;
	reg [11:0] i_bank;		
	reg [11:0] i_wait;		
	reg [11:0] i_data_mosi;
	reg spi_activ;
	reg hri1; reg hri2; reg hri3; reg hri4;
	//
	wire spi_cs_fe;
	wire spi_cs_re;
	wire spi_clk_re;
	wire spi_clk_fe;
	// Filter der Eingaenge
	wire spi_cs_filter;
	wire spi_clk_filter;
	wire spi_mosi_filter;	
	wire spi_write_rgb;
	
	parameter SPI_FILTER = 5'd5;
	SPI_INP_FILTER_RGB_HOST spi_inp_filter_cs(CLK, SPI_CS, spi_cs_filter);       defparam spi_inp_filter_cs.FILTER = SPI_FILTER;
	SPI_INP_FILTER_RGB_HOST spi_inp_filter_clk(CLK, SPI_CLK, spi_clk_filter);    defparam spi_inp_filter_clk.FILTER = SPI_FILTER;
	SPI_INP_FILTER_RGB_HOST spi_inp_filter_mosi(CLK, SPI_MOSI, spi_mosi_filter); defparam spi_inp_filter_mosi.FILTER = SPI_FILTER;
	// Glue Logic
	assign spi_write_rgb = spi_activ & cmd_temp[0] & cmd_temp[3];// ENABLE, READ, WRITE RGB
	assign spi_cs_re = (hri1 && !hri2);
	assign spi_cs_fe = (!hri1 && hri2);
	assign spi_clk_re = (hri3 && !hri4 && spi_activ);
	assign spi_clk_fe = (!hri3 && hri4 && spi_activ);
	//	
	initial
	begin
		DATA_WRITE_COPY <= 0;
		BANK <= 0;
		DATA_OUT <= 0;	
		//
		spi_activ <= 0;
		cmd_temp <= 0;
		bank_temp <= 0;
		data_out_temp <= 0;
		spi_clk_ctr <= 0;
		i_cmd <= 0;
		i_bank <= 0;	
		i_wait <= 0;
		i_data_mosi <= 0;
		//
		hri1 <= 0; hri2 <= 0; hri3 <= 0; hri4 <= 0;		
	end	
	//
	always	@(posedge CLK)
	begin
	//
	hri1 <= spi_cs_filter;
	hri2 <= hri1;			
	//
	if (spi_cs_fe) 
		begin
		spi_activ <= 1;
		spi_clk_ctr <= 0;
		cmd_temp <= 0;
		bank_temp <= 0;
		//data_out_temp <= 0;				
		i_cmd <= 0;
		i_bank <= 0;	
		i_wait <= 0;
		i_data_mosi <= 0;
		end
	//
	// Counter SPI_CLK
	hri3 <= spi_clk_filter;
	hri4 <= hri3;
	if (spi_clk_re && (spi_clk_ctr < 280))
		begin
		spi_clk_ctr <= spi_clk_ctr + 1;
		end
	// SPI Kommunkation beendet
	if (spi_cs_re) 
		begin
		spi_activ <= 0;
		DATA_WRITE_COPY <= spi_write_rgb;// write cmd
		DATA_OUT <= data_out_temp;	
		end	
	else
		begin
		DATA_WRITE_COPY <= 0;
		end
		
	// SPI Kommunikation aktiv
	if (spi_clk_re && spi_activ)
		begin
		// Kommando und Adresse ausgeben
		if ((spi_clk_ctr == 20))
			begin
			BANK <= bank_temp;
			end
		// Kommandobyte
		if (spi_clk_ctr < 8)
			begin
			cmd_temp[i_cmd] <= spi_mosi_filter;
			i_cmd <= i_cmd + 1;
			end
		// BANK Byte
		else if (spi_clk_ctr < 16)
			begin
			bank_temp[i_bank] <= spi_mosi_filter;
			i_bank <= i_bank + 1;
			end
		// wait Byte
		else if (spi_clk_ctr < 24)
			begin
			i_wait <= i_wait + 1;
			end
		// Datenempfang
		else if (spi_clk_ctr < 280)
			begin
			if (cmd_temp[3] && (i_data_mosi < 256))
				begin
				data_out_temp[i_data_mosi] <= spi_mosi_filter;
				end
			i_data_mosi <= i_data_mosi + 1;
			end
		end
	end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////
//	Digitales Filter
module	SPI_INP_FILTER_RGB_HOST (
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