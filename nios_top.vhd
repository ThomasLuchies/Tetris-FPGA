-- Implements a simple Nios II system for the DE-series board
library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity nios_top IS 
	 port (
		 CLOCK_50 : in std_logic;
		 KEY : in std_logic_vector (3 DOWNTO 0);
		 SW : in std_logic_vector (17 DOWNTO 0);
		 LEDR : out std_logic_vector (17 DOWNTO 0);
		 
		 --sram
		 SRAM_DQ: inout std_logic_vector(15 downto 0);
		 SRAM_UB_N, SRAM_LB_N, SRAM_CE_N,	SRAM_OE_N, SRAM_WE_N: out std_logic;
		 SRAM_ADDR: out std_logic_vector(19 downto 0)
	 );
end nios_top;

ARCHITECTURE nios_top_rtl OF nios_top IS
	
	
	component sram_tester 
	port
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
	end component;
	BEGIN
		
		 
		 tester: sram_tester PORT MAP (
			clk => CLOCK_50,
			SW => SW,
			KEY => KEY,
			LEDR => LEDR,
			SRAM_DQ => SRAM_DQ,
			SRAM_UB_N => SRAM_UB_N,
			SRAM_LB_N => SRAM_LB_N,
			SRAM_CE_N => SRAM_CE_N,
			SRAM_OE_N => SRAM_OE_N,
			SRAM_WE_N => SRAM_WE_N,
			SRAM_ADDR => SRAM_ADDR
		); 
		 
END nios_top_rtl;