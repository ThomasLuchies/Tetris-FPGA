LIBRARY ieee;
USE ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

entity tetris is
	generic(
		reset_n		: std_logic := '0'
	);
	port(
		CLOCK_50		:  in    std_logic;
		h_sync		:	OUT	STD_LOGIC;	--horiztonal sync pulse
		v_sync		:	OUT	STD_LOGIC;	--vertical sync pulse
		n_blank		:	OUT	STD_LOGIC;	--direct blacking output to DAC
		n_sync		:	OUT	STD_LOGIC; --sync-on-green output to DAC
		VGA_R       :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --red magnitude output to DAC
		VGA_G    	:  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --green magnitude output to DAC
		VGA_B    	:  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0'); --blue magnitude output to DAC
		VGA_CLK		:  out	std_logic
	);
end entity;

architecture tetris_arch of tetris is
	component pixel_clock is
		port
		(
			areset		: IN STD_LOGIC  := '0';
			inclk0		: IN STD_LOGIC  := '0';
			c0				: OUT STD_LOGIC 
		);
	end component pixel_clock;

	component vga_controller is
		generic(
			h_pulse 	:	INTEGER := 72;    	--horiztonal sync pulse width in pixels
			h_bp	 	:	INTEGER := 128;		--horiztonal back porch width in pixels
			h_pixels	:	INTEGER := 800;		--horiztonal display width in pixels
			h_fp	 	:	INTEGER := 24;		   --horiztonal front porch width in pixels
			h_pol		:	STD_LOGIC := '1';		--horizontal sync pulse polarity (1 = positive, 0 = negative)
			v_pulse 	:	INTEGER := 2;			--vertical sync pulse width in rows
			v_bp	 	:	INTEGER := 22;			--vertical back porch width in rows
			v_pixels	:	INTEGER := 600;		--vertical display width in rows
			v_fp	 	:	INTEGER := 1;			--vertical front porch width in rows
			v_pol		:	STD_LOGIC := '1');	--vertical sync pulse polarity (1 = positive, 0 = negative)
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
		 pixels_y :  INTEGER := 478;   --row that first color will persist until
		 pixels_x :  INTEGER := 600);  --column that first color will persist until
	  port(
		 disp_ena :  IN   STD_LOGIC;  --display enable ('1' = display time, '0' = blanking time)
		 row      :  IN   INTEGER;    --row pixel coordinate
		 column   :  IN   INTEGER;    --column pixel coordinate
		 red      :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --red magnitude output to DAC
		 green    :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');  --green magnitude output to DAC
		 blue     :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0')); --blue magnitude output to DAC
	end component;
	
	signal row: integer;
	signal column: integer;
	signal pixel_clk: std_logic;
	signal disp_ena: std_logic;
begin 
	VGA_CLK <= pixel_clk;
	pc0: pixel_clock port map(
													areset => '0',
													inclk0 => CLOCK_50,
													c0 => pixel_clk
												);
	vga_c0: vga_controller port map(
														pixel_clk => pixel_clk,
														reset_n => '1',
														h_sync => h_sync,
														v_sync => v_sync,
														disp_ena => disp_ena,
														column => column,
														row => row,
														n_blank => n_blank,
														n_sync => n_sync
														);

	ig0: image_generator port map( 
															disp_ena => disp_ena,
															row => row,
															column => column,
															red => VGA_R,
															green => VGA_G,
															blue => VGA_B
														);
															
end architecture tetris_arch;