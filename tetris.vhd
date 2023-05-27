LIBRARY ieee;
USE ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

entity tetris is
	generic(
		reset_n		: std_logic := '0'
	);
	port(
		clk		:  in    std_logic;
		h_sync		:	OUT	STD_LOGIC;	--horiztonal sync pulse
		v_sync		:	OUT	STD_LOGIC;	--vertical sync pulse
		n_blank		:	OUT	STD_LOGIC;	--direct blacking output to DAC
		n_sync		:	OUT	STD_LOGIC; --sync-on-green output to DAC
		red       :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0);  --red magnitude output to DAC
		green    	:  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0);  --green magnitude output to DAC
		blue    	:  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0); --blue magnitude output to DAC
		VGA_clk		:  out	std_logic
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

	component vga_controller is
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
	end component vga_controller;
	
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
		 blue     :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)); --blue magnitude output to DAC
	end component;
	
	signal row: integer;
	signal column: integer;
	signal pixel_clk: std_logic;
	signal disp_ena: std_logic;
begin 
	VGA_clk <= pixel_clk;
	
	pc0: pixel_clock 
	port map(
		areset => '0',
		inclk0 => clk,
		c0 => pixel_clk
	);
	
	vga_c0: vga_controller 
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
		h_sync => h_sync,
		v_sync => v_sync,
		disp_ena => disp_ena,
		column => row,
		row => column,
		n_blank => n_blank,
		n_sync => n_sync
	);

	ig0: image_generator 
	GENERIC MAP(
		pixels_x => 478,
		pixels_y => 600
	)
	port map( 
		clk => clk,
		disp_ena => disp_ena,
		row => row,
		column => column,
		red => red,
		green => green,
		blue => blue
	);
															
end architecture tetris_arch;