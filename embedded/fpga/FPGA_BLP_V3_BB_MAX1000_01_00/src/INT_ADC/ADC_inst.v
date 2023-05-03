	ADC u0 (
		.clk_clk                               (<connected-to-clk_clk>),                               //                          clk.clk
		.modular_adc_0_adc_pll_clock_clk       (<connected-to-modular_adc_0_adc_pll_clock_clk>),       //  modular_adc_0_adc_pll_clock.clk
		.modular_adc_0_adc_pll_locked_export   (<connected-to-modular_adc_0_adc_pll_locked_export>),   // modular_adc_0_adc_pll_locked.export
		.modular_adc_0_response_valid          (<connected-to-modular_adc_0_response_valid>),          //       modular_adc_0_response.valid
		.modular_adc_0_response_channel        (<connected-to-modular_adc_0_response_channel>),        //                             .channel
		.modular_adc_0_response_data           (<connected-to-modular_adc_0_response_data>),           //                             .data
		.modular_adc_0_response_startofpacket  (<connected-to-modular_adc_0_response_startofpacket>),  //                             .startofpacket
		.modular_adc_0_response_endofpacket    (<connected-to-modular_adc_0_response_endofpacket>),    //                             .endofpacket
		.modular_adc_0_sequencer_csr_address   (<connected-to-modular_adc_0_sequencer_csr_address>),   //  modular_adc_0_sequencer_csr.address
		.modular_adc_0_sequencer_csr_read      (<connected-to-modular_adc_0_sequencer_csr_read>),      //                             .read
		.modular_adc_0_sequencer_csr_write     (<connected-to-modular_adc_0_sequencer_csr_write>),     //                             .write
		.modular_adc_0_sequencer_csr_writedata (<connected-to-modular_adc_0_sequencer_csr_writedata>), //                             .writedata
		.modular_adc_0_sequencer_csr_readdata  (<connected-to-modular_adc_0_sequencer_csr_readdata>),  //                             .readdata
		.reset_reset_n                         (<connected-to-reset_reset_n>)                          //                        reset.reset_n
	);

