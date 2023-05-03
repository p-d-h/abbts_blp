	component ISSP is
		port (
			source : out std_logic_vector(0 downto 0)   -- source
		);
	end component ISSP;

	u0 : component ISSP
		port map (
			source => CONNECTED_TO_source  -- sources.source
		);

