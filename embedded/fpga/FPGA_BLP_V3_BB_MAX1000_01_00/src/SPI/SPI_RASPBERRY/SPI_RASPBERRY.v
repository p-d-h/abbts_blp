////////////////////////////////////////////////////////////////////////////////////////////
module SPI_RASPBERRY (
	input CLK,
	input SPI_CS,
	input SPI_CLK,
	input SPI_MOSI,
	input [1023:0] DATA_TX,
	input RESET,
	output SPI_MISO_TRI,
	output reg SPI_MISO,
	output reg [1023:0] DATA_RX,
	output SPI_READ,
	output SPI_WRITE
	);
	//
	reg [1031:0] data_tx_temp;
	reg [1031:0] data_rx_temp;		
	reg [11:0] spi_clk_ctr;
	reg [11:0] i_ctr_data_rx;
	reg [11:0] i_ctr_data_tx;
	//
	reg spi_activ;
	reg test_rx_data;
	reg spi_cs_fe_delay;
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
	
	parameter SPI_FILTER = 5'd5;
	SPI_INP_FILTER_RPI spi_inp_filter_cs(CLK, SPI_CS, spi_cs_filter);       
	defparam spi_inp_filter_cs.FILTER = SPI_FILTER;
	SPI_INP_FILTER_RPI spi_inp_filter_clk(CLK, SPI_CLK, spi_clk_filter);    
	defparam spi_inp_filter_clk.FILTER = SPI_FILTER;
	SPI_INP_FILTER_RPI spi_inp_filter_mosi(CLK, SPI_MOSI, spi_mosi_filter); 
	defparam spi_inp_filter_mosi.FILTER = SPI_FILTER;
	
	// Glue Logic
	assign SPI_READ = spi_activ & data_rx_temp[0] & data_rx_temp[1];// ENABLE, READ
	assign SPI_WRITE = spi_activ & data_rx_temp[0] & data_rx_temp[2];// ENABLE, WRITE
	assign SPI_MISO_TRI = SPI_READ;
	assign spi_cs_re = (hri1 && !hri2);
	assign spi_cs_fe = (!hri1 && hri2);
	assign spi_clk_re = (hri3 && !hri4 && spi_activ);
	assign spi_clk_fe = (!hri3 && hri4 && spi_activ);
	//	
	initial
	begin
		SPI_MISO <= 0;
		DATA_RX <= 0;	
		//
		spi_activ <= 0;	
		data_tx_temp <= 0;
		data_rx_temp <= 0;
		test_rx_data <= 0;
		spi_cs_fe_delay <= 0;
		spi_clk_ctr <= 0;
		i_ctr_data_tx <= 0;
		i_ctr_data_rx <= 0;
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
	if (RESET) 
		begin
		DATA_RX <= 0;
		end
	//
	if (spi_cs_fe) 
		begin
		spi_activ <= 1;
		spi_clk_ctr <= 0;
		data_tx_temp[1023:0] <= DATA_TX;
		data_rx_temp <= 0;				
		i_ctr_data_tx <= 0;
		i_ctr_data_rx <= 0;
		end
	//
	// Counter SPI_CLK
	hri3 <= spi_clk_filter;
	hri4 <= hri3;
	if (spi_clk_re)
		begin
		spi_clk_ctr <= spi_clk_ctr + 1;
		end
	if (spi_clk_ctr < 1027) // 4 Bits Reserve
		begin
		// Datenempfang
		if (spi_clk_re)
			begin
			if ((i_ctr_data_rx < 8) | SPI_WRITE)
				begin
				data_rx_temp[i_ctr_data_rx] <= spi_mosi_filter;
				end
			test_rx_data <= spi_mosi_filter;
			i_ctr_data_rx <= i_ctr_data_rx + 1;
			end
		// Datenversand
		spi_cs_fe_delay <= spi_cs_fe;
		if (spi_clk_fe || spi_cs_fe_delay)
			begin
			if ((i_ctr_data_tx < 8) | SPI_READ)
				begin
				SPI_MISO <= data_tx_temp[i_ctr_data_tx];
				end
			i_ctr_data_tx <= i_ctr_data_tx + 1;
			end
		end
	// SPI Kommunkation beendet
	if (spi_cs_re) 
		begin
		spi_activ <= 0;
		SPI_MISO <= 0;
		if (SPI_WRITE)
			begin
			DATA_RX <= data_rx_temp[1023:0];	
			end
		end
	end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////
//	Digitales Filter der Eingangssignale
module	SPI_INP_FILTER_RPI (
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
	if (FILTER == 0)
		begin
		OUT = IN;
		end
	else
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
end
endmodule
////////////////////////////////////////////////////////////////////////////////////////////