library ieee;
use ieee.std_logic_1164.all;

entity sram_tester is port
(
	clk : in std_logic;

	-- user control
	SW : in std_logic_vector(17 downto 0);
	KEY : in std_logic_vector(3 downto 0);
	LEDR : out std_logic_vector(17 downto 0);

	-- sram_controller side
	SRAM_DQ : inout std_logic_vector(15 downto 0);
	SRAM_UB_N, SRAM_LB_N, SRAM_CE_N,	SRAM_OE_N, SRAM_WE_N	: out std_logic;
	SRAM_ADDR : out std_logic_vector(19 downto 0)
);
end entity;

architecture rtl of sram_tester is	

	component  nios2 is
		port (
			clk_clk         : in  std_logic                     := '0';             --      clk.clk
			leds_export     : out std_logic_vector(17 downto 0);                    --     leds.export
			reset_reset_n   : in  std_logic                     := '0';             --    reset.reset_n
			switches_export : in  std_logic_vector(17 downto 0) := (others => '0')  -- switches.export
		);
	end component;
	signal target_address : std_logic_vector(19 downto 0) := (others => '0');
	signal leds: std_logic_vector(17 downto 0);
	signal switches: std_logic_vector(17 downto 0);

begin

	ni: nios2 port map
	(
		clk_clk => clk,
		leds_export => leds,
		reset_reset_n => KEY(3),
		switches_export => switches
	);
	sram_controller : entity work.sram_controller port map
	(
		clk => clk,
		-- schematic side
		read_n => key(0),
		write_n => key(1),
		clear_sram => key(2),
		data_input => sw(15 downto 0),
		addr_input => target_address,
		data_output => ledr(15 downto 0),
		-- sram side
		data => SRAM_DQ,
		address => SRAM_ADDR,
		output_enable_n => SRAM_OE_N,
		write_enable_n => SRAM_WE_N,
      chip_select_n => SRAM_CE_N,
		ub_n => SRAM_UB_N,
		lb_n => SRAM_LB_N
	);
	
	target_address <= x"0000F" when sw(17) = '1' else (others => '0');
	ledr(17 downto 16) <= (others => '0');

end architecture;