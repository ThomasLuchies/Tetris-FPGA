	component sram is
		port (
			clk_clk        : in    std_logic                     := 'X';             -- clk
			reset_reset_n  : in    std_logic                     := 'X';             -- reset_n
			row_0_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_1_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_10_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_11_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_12_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_13_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_14_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_15_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_16_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_17_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_18_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_19_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_2_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_20_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_21_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_22_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_23_export  : out   std_logic_vector(29 downto 0);                    -- export
			row_3_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_4_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_5_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_6_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_7_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_8_export   : out   std_logic_vector(29 downto 0);                    -- export
			row_9_export   : out   std_logic_vector(29 downto 0);                    -- export
			sram_DQ        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DQ
			sram_ADDR      : out   std_logic_vector(19 downto 0);                    -- ADDR
			sram_LB_N      : out   std_logic;                                        -- LB_N
			sram_UB_N      : out   std_logic;                                        -- UB_N
			sram_CE_N      : out   std_logic;                                        -- CE_N
			sram_OE_N      : out   std_logic;                                        -- OE_N
			sram_WE_N      : out   std_logic;                                        -- WE_N
			buttons_export : in    std_logic_vector(3 downto 0)  := (others => 'X')  -- export
		);
	end component sram;

	u0 : component sram
		port map (
			clk_clk        => CONNECTED_TO_clk_clk,        --     clk.clk
			reset_reset_n  => CONNECTED_TO_reset_reset_n,  --   reset.reset_n
			row_0_export   => CONNECTED_TO_row_0_export,   --   row_0.export
			row_1_export   => CONNECTED_TO_row_1_export,   --   row_1.export
			row_10_export  => CONNECTED_TO_row_10_export,  --  row_10.export
			row_11_export  => CONNECTED_TO_row_11_export,  --  row_11.export
			row_12_export  => CONNECTED_TO_row_12_export,  --  row_12.export
			row_13_export  => CONNECTED_TO_row_13_export,  --  row_13.export
			row_14_export  => CONNECTED_TO_row_14_export,  --  row_14.export
			row_15_export  => CONNECTED_TO_row_15_export,  --  row_15.export
			row_16_export  => CONNECTED_TO_row_16_export,  --  row_16.export
			row_17_export  => CONNECTED_TO_row_17_export,  --  row_17.export
			row_18_export  => CONNECTED_TO_row_18_export,  --  row_18.export
			row_19_export  => CONNECTED_TO_row_19_export,  --  row_19.export
			row_2_export   => CONNECTED_TO_row_2_export,   --   row_2.export
			row_20_export  => CONNECTED_TO_row_20_export,  --  row_20.export
			row_21_export  => CONNECTED_TO_row_21_export,  --  row_21.export
			row_22_export  => CONNECTED_TO_row_22_export,  --  row_22.export
			row_23_export  => CONNECTED_TO_row_23_export,  --  row_23.export
			row_3_export   => CONNECTED_TO_row_3_export,   --   row_3.export
			row_4_export   => CONNECTED_TO_row_4_export,   --   row_4.export
			row_5_export   => CONNECTED_TO_row_5_export,   --   row_5.export
			row_6_export   => CONNECTED_TO_row_6_export,   --   row_6.export
			row_7_export   => CONNECTED_TO_row_7_export,   --   row_7.export
			row_8_export   => CONNECTED_TO_row_8_export,   --   row_8.export
			row_9_export   => CONNECTED_TO_row_9_export,   --   row_9.export
			sram_DQ        => CONNECTED_TO_sram_DQ,        --    sram.DQ
			sram_ADDR      => CONNECTED_TO_sram_ADDR,      --        .ADDR
			sram_LB_N      => CONNECTED_TO_sram_LB_N,      --        .LB_N
			sram_UB_N      => CONNECTED_TO_sram_UB_N,      --        .UB_N
			sram_CE_N      => CONNECTED_TO_sram_CE_N,      --        .CE_N
			sram_OE_N      => CONNECTED_TO_sram_OE_N,      --        .OE_N
			sram_WE_N      => CONNECTED_TO_sram_WE_N,      --        .WE_N
			buttons_export => CONNECTED_TO_buttons_export  -- buttons.export
		);

