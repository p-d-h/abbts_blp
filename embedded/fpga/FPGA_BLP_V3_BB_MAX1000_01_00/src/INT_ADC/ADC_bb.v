
module ADC (
	clk_clk,
	modular_adc_0_adc_pll_clock_clk,
	modular_adc_0_adc_pll_locked_export,
	modular_adc_0_response_valid,
	modular_adc_0_response_channel,
	modular_adc_0_response_data,
	modular_adc_0_response_startofpacket,
	modular_adc_0_response_endofpacket,
	modular_adc_0_sequencer_csr_address,
	modular_adc_0_sequencer_csr_read,
	modular_adc_0_sequencer_csr_write,
	modular_adc_0_sequencer_csr_writedata,
	modular_adc_0_sequencer_csr_readdata,
	reset_reset_n);	

	input		clk_clk;
	input		modular_adc_0_adc_pll_clock_clk;
	input		modular_adc_0_adc_pll_locked_export;
	output		modular_adc_0_response_valid;
	output	[4:0]	modular_adc_0_response_channel;
	output	[11:0]	modular_adc_0_response_data;
	output		modular_adc_0_response_startofpacket;
	output		modular_adc_0_response_endofpacket;
	input		modular_adc_0_sequencer_csr_address;
	input		modular_adc_0_sequencer_csr_read;
	input		modular_adc_0_sequencer_csr_write;
	input	[31:0]	modular_adc_0_sequencer_csr_writedata;
	output	[31:0]	modular_adc_0_sequencer_csr_readdata;
	input		reset_reset_n;
endmodule
