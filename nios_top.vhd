-- Implements a simple Nios II system for the DE-series board
library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity nios_top IS 
	 port (
		 CLOCK_50 : in std_logic;
		 KEY : in std_logic_vector (0 DOWNTO 0);
		 SW : in std_logic_vector (17 DOWNTO 0);
		 LEDR : out std_logic_vector (17 DOWNTO 0);
		 
		 --sram
		 SRAM_DQ: inout std_logic_vector(15 downto 0);
		 SRAM_UB_N, SRAM_LB_N, SRAM_CE_N,	SRAM_OE_N, SRAM_WE_N: out std_logic;
		 SRAM_ADDR: out std_logic_vector(19 downto 0)
	 );
end nios_top;

ARCHITECTURE nios_top_rtl OF nios_top IS
	COMPONENT sram
			port (
				clk_clk       : in    std_logic                     := '0';             --   clk.clk
				reset_reset_n : in    std_logic                     := '0';             -- reset.reset_n
				sram_DQ       : inout std_logic_vector(15 downto 0) := (others => '0'); --  sram.DQ
				sram_ADDR     : out   std_logic_vector(19 downto 0);                    --      .ADDR
				sram_LB_N     : out   std_logic;                                        --      .LB_N
				sram_UB_N     : out   std_logic;                                        --      .UB_N
				sram_CE_N     : out   std_logic;                                        --      .CE_N
				sram_OE_N     : out   std_logic;                                        --      .OE_N
				sram_WE_N     : out   std_logic                                         --      .WE_N
	);
	END COMPONENT;
	
	component image_generator IS
	GENERIC(
		pixels_y :	INTEGER := 480;    --row that first color will persist until
		pixels_x	:	INTEGER := 640;
		lastPixel : INTEGER := 0;   --column that first color will persist until
		currentPixel : INTEGER := 0);
	PORT(
		clk			:  in 	std_logic;
		disp_ena		:	IN		STD_LOGIC;	--display enable ('1' = display time, '0' = blanking time)
		row			:	IN		INTEGER;		--row pixel coordinate
		column		:	IN		INTEGER;		--column pixel coordinate
		red			:	OUT	STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --red magnitude output to DAC
		green			:	OUT	STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --green magnitude output to DAC
		blue			:	OUT	STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0'); --blue magnitude output to DAC
		
		-- SRAM
		data : inout std_logic_vector(15 downto 0);
		address : out std_logic_vector(19 downto 0);
		output_enable_n : out std_logic := '1';
		write_enable_n : buffer std_logic := '1';
		chip_select_n : out std_logic := '1';
		ub_n : out std_logic := '0'; -- always active
		lb_n : out std_logic := '0'); -- always active
END component;
	BEGIN
		 NiosII : sram PORT MAP(
			 clk_clk => CLOCK_50,
			 reset_reset_n => KEY(0),
			 sram_DQ =>sram_DQ,
				sram_ADDR =>sram_ADDR,
				sram_LB_N =>sram_LB_N,
				sram_UB_N =>sram_UB_N,
				sram_CE_N =>sram_CE_N,
				sram_OE_N =>sram_OE_N,
				sram_WE_N =>sram_WE_N
		 );
		 
END nios_top_rtl;