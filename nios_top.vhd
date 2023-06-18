-- Implements a simple Nios II system for the DE-series board
library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity nios_top IS 
	 port (
		 CLOCK_50 : in std_logic;
		 KEY : in std_logic_vector (0 DOWNTO 0);
		 SW : in std_logic_vector (17 DOWNTO 0);
		 LEDR : out std_logic_vector (17 DOWNTO 0) 
	 );
end nios_top;

ARCHITECTURE nios_top_rtl OF nios_top IS
	COMPONENT nios2
		port (
			clk_clk : in std_logic := '0';
			leds_export : out std_logic_vector(17 downto 0);
			reset_reset_n : in std_logic := '0';
			switches_export : in std_logic_vector(17 downto 0) := (others => '0')
		);
	END COMPONENT;
	BEGIN
		 NiosII : nios2 PORT MAP(
			 clk_clk => CLOCK_50,
			 reset_reset_n => KEY(0),
			 leds_export => LEDR(17 DOWNTO 0),
			 switches_export => SW(17 DOWNTO 0) 
		 );
END nios_top_rtl;