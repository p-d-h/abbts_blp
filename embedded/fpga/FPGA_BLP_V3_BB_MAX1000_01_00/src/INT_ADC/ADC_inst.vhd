	component ADC is
		port (
			clk_clk                               : in  std_logic                     := 'X';             -- clk
			modular_adc_0_adc_pll_clock_clk       : in  std_logic                     := 'X';             -- clk
			modular_adc_0_adc_pll_locked_export   : in  std_logic                     := 'X';             -- export
			modular_adc_0_response_valid          : out std_logic;                                        -- valid
			modular_adc_0_response_channel        : out std_logic_vector(4 downto 0);                     -- channel
			modular_adc_0_response_data           : out std_logic_vector(11 downto 0);                    -- data
			modular_adc_0_response_startofpacket  : out std_logic;                                        -- startofpacket
			modular_adc_0_response_endofpacket    : out std_logic;                                        -- endofpacket
			modular_adc_0_sequencer_csr_address   : in  std_logic                     := 'X';             -- address
			modular_adc_0_sequencer_csr_read      : in  std_logic                     := 'X';             -- read
			modular_adc_0_sequencer_csr_write     : in  std_logic                     := 'X';             -- write
			modular_adc_0_sequencer_csr_writedata : in  std_logic_vector(31 downto 0) := (others => 'X'); -- writedata
			modular_adc_0_sequencer_csr_readdata  : out std_logic_vector(31 downto 0);                    -- readdata
			reset_reset_n                         : in  std_logic                     := 'X'              -- reset_n
		);
	end component ADC;

	u0 : component ADC
		port map (
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                          clk.clk
			modular_adc_0_adc_pll_clock_clk       => CONNECTED_TO_modular_adc_0_adc_pll_clock_clk,       --  modular_adc_0_adc_pll_clock.clk
			modular_adc_0_adc_pll_locked_export   => CONNECTED_TO_modular_adc_0_adc_pll_locked_export,   -- modular_adc_0_adc_pll_locked.export
			modular_adc_0_response_valid          => CONNECTED_TO_modular_adc_0_response_valid,          --       modular_adc_0_response.valid
			modular_adc_0_response_channel        => CONNECTED_TO_modular_adc_0_response_channel,        --                             .channel
			modular_adc_0_response_data           => CONNECTED_TO_modular_adc_0_response_data,           --                             .data
			modular_adc_0_response_startofpacket  => CONNECTED_TO_modular_adc_0_response_startofpacket,  --                             .startofpacket
			modular_adc_0_response_endofpacket    => CONNECTED_TO_modular_adc_0_response_endofpacket,    --                             .endofpacket
			modular_adc_0_sequencer_csr_address   => CONNECTED_TO_modular_adc_0_sequencer_csr_address,   --  modular_adc_0_sequencer_csr.address
			modular_adc_0_sequencer_csr_read      => CONNECTED_TO_modular_adc_0_sequencer_csr_read,      --                             .read
			modular_adc_0_sequencer_csr_write     => CONNECTED_TO_modular_adc_0_sequencer_csr_write,     --                             .write
			modular_adc_0_sequencer_csr_writedata => CONNECTED_TO_modular_adc_0_sequencer_csr_writedata, --                             .writedata
			modular_adc_0_sequencer_csr_readdata  => CONNECTED_TO_modular_adc_0_sequencer_csr_readdata,  --                             .readdata
			reset_reset_n                         => CONNECTED_TO_reset_reset_n                          --                        reset.reset_n
		);

