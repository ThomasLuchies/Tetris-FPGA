LIBRARY ieee;
USE ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

entity tetris is
	generic(
		reset_n		: std_logic := '0'
	);
	port(
		CLOCK_50		:  in    std_logic;
		VGA_BLANK_N: out std_logic;
	   VGA_B: out std_logic_vector(7 downto 0);
	   VGA_CLK: out std_logic;
	   VGA_G: out std_logic_vector(7 downto 0);
	   VGA_HS: out std_logic;
	   VGA_R: out std_logic_vector(7 downto 0);
	   VGA_SYNC_N: out std_logic;
	   VGA_VS: out std_logic;
		
		-- NIOS inputs and outputs
		KEY : in std_logic_vector (0 DOWNTO 0);
		SW : in std_logic_vector (17 DOWNTO 0);
		LEDR : out std_logic_vector (17 DOWNTO 0);
		LEDG : out std_logic_vector(7 downto 0);
		
		--sram
		SRAM_DQ: inout std_logic_vector(15 downto 0);
		SRAM_UB_N, SRAM_LB_N, SRAM_CE_N,	SRAM_OE_N, SRAM_WE_N: out std_logic;
		SRAM_ADDR: out std_logic_vector(19 downto 0)
	);
end entity;

architecture tetris_arch of tetris is
	component pixel_clock is
		port
		(
			areset		: IN STD_LOGIC;
			inclk0		: IN STD_LOGIC;
			c0				: OUT STD_LOGIC 
		);
	end component pixel_clock;

	component vga_controller_vhd is
		generic(
			h_pulse 	:	INTEGER;    	--horiztonal sync pulse width in pixels
			h_bp	 	:	INTEGER;		--horiztonal back porch width in pixels
			h_pixels	:	INTEGER;		--horiztonal display width in pixels
			h_fp	 	:	INTEGER;		   --horiztonal front porch width in pixels
			h_pol		:	STD_LOGIC;		--horizontal sync pulse polarity (1 = positive, 0 = negative)
			v_pulse 	:	INTEGER;			--vertical sync pulse width in rows
			v_bp	 	:	INTEGER;			--vertical back porch width in rows
			v_pixels	:	INTEGER;		--vertical display width in rows
			v_fp	 	:	INTEGER;			--vertical front porch width in rows
			v_pol		:	STD_LOGIC);	--vertical sync pulse polarity (1 = positive, 0 = negative)
		port( 
			pixel_clk   : in std_logic;
			reset_n		:	IN		STD_LOGIC;	--active low asycnchronous reset
			h_sync		:	OUT	STD_LOGIC;	--horiztonal sync pulse
			v_sync		:	OUT	STD_LOGIC;	--vertical sync pulse
			disp_ena		:	OUT	STD_LOGIC;	--display enable ('1' = display time, '0' = blanking time)
			column		:	OUT	INTEGER;		--horizontal pixel coordinate
			row			:	OUT	INTEGER;		--vertical pixel coordinate
			n_blank		:	OUT	STD_LOGIC;	--direct blacking output to DAC
			n_sync		:	OUT	STD_LOGIC --sync-on-green output to DAC
		);
	end component vga_controller_vhd;
	
	component image_generator is
	  generic(
		 pixels_y :  INTEGER;   --row that first color will persist until
		 pixels_x :  INTEGER);  --column that first color will persist until
	  port(
	    clk		 :  in 	std_logic;
		 disp_ena :  IN   STD_LOGIC;  --display enable ('1' = display time, '0' = blanking time)
		 row      :  IN   INTEGER;    --row pixel coordinate
		 column   :  IN   INTEGER;    --column pixel coordinate
		 red      :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0);  --red magnitude output to DAC
		 green    :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0);  --green magnitude output to DAC
		 blue     :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0); --blue magnitude output to DAC
		 LEDG : out std_logic_vector(7 downto 0);
		 
		 -- SRAM
		data : inout std_logic_vector(15 downto 0);
		address : out std_logic_vector(19 downto 0);
		output_enable_n : out std_logic := '1';
		write_enable_n : buffer std_logic := '1';
		chip_select_n : out std_logic := '1';
		ub_n : out std_logic := '0'; -- always active
		lb_n : out std_logic := '0'); -- always active
	end component;
	
	COMPONENT nios2
		port (
			clk_clk : in std_logic := '0';
			leds_export : out std_logic_vector(17 downto 0);
			reset_reset_n : in std_logic := '0';
			switches_export : in std_logic_vector(17 downto 0) := (others => '0')
		);
	END COMPONENT;
	
	signal row: integer;
	signal column: integer;
	signal pixel_clk: std_logic;
	signal disp_ena: std_logic;
begin 
	VGA_CLK <= pixel_clk;
	
	 NiosII : nios2 PORT MAP(
		 clk_clk => CLOCK_50,
		 reset_reset_n => KEY(0),
		 leds_export => LEDR(17 DOWNTO 0),
		 switches_export => SW(17 DOWNTO 0) 
	 );
	
	pc0: pixel_clock 
	port map(
		areset => '0',
		inclk0 => CLOCK_50,
		c0 => pixel_clk
	);
	
	vga_c0: vga_controller_vhd 
	GENERIC MAP(h_bp => 48,
			h_fp => 16,
			h_pixels => 640,
			h_pol => '0',
			h_pulse => 96,
			v_bp => 33,
			v_fp => 10,
			v_pixels => 480,
			v_pol => '0',
			v_pulse => 2
	)
	port map(
		pixel_clk => pixel_clk,
		reset_n => '1',
		h_sync => VGA_HS,
		v_sync => VGA_VS,
		disp_ena => disp_ena,
		column => row,
		row => column,
		n_blank => VGA_BLANK_N,
		n_sync => VGA_SYNC_N
		
	);

	ig0: image_generator 
	GENERIC MAP(
		pixels_x => 478,
		pixels_y => 600
	)
	port map( 
		clk => CLOCK_50,
		disp_ena => disp_ena,
		row => row,
		column => column,
		red => VGA_R,
		green => VGA_G,
		blue => VGA_B,
		LEDG => LEDG,
		data => SRAM_DQ,
		address => SRAM_ADDR,
		output_enable_n => SRAM_OE_N,
		write_enable_n => SRAM_WE_N,
		chip_select_n => SRAM_CE_N,
		ub_n => SRAM_UB_N,
		lb_n => SRAM_LB_N 
	);
															
end architecture tetris_arch;