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
		KEY : in std_logic_vector (3 DOWNTO 0);
		SW : in std_logic_vector (17 DOWNTO 0);
		LEDR : out std_logic_vector (17 DOWNTO 0);
		LEDG : out std_logic_vector(7 downto 0);
		
		--sram
		SRAM_DQ: inout std_logic_vector(15 downto 0);
		SRAM_UB_N, SRAM_LB_N, SRAM_CE_N,	SRAM_OE_N, SRAM_WE_N: out std_logic;
		SRAM_ADDR: out std_logic_vector(19 downto 0);
		
		-- HEX displays
		HEX0: out std_logic_vector(6 downto 0);
		HEX1: out std_logic_vector(6 downto 0);
		HEX2: out std_logic_vector(6 downto 0);
		HEX3: out std_logic_vector(6 downto 0);
		HEX4: out std_logic_vector(6 downto 0);
		HEX5: out std_logic_vector(6 downto 0);
		HEX6: out std_logic_vector(6 downto 0);
		HEX7: out std_logic_vector(6 downto 0)
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
		 display  :  IN 	std_logic_vector(719 downto 0);
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
	
	COMPONENT sram
		port (
			clk_clk : in std_logic := '0';
			move_left_export    : in    std_logic                     := '0';             --    move_left.export
			move_right_export   : in    std_logic                     := '0';             --   move_right.export
			reset_reset_n       : in    std_logic                     := '0';             --        reset.reset_n
			rotate_left_export  : in    std_logic                     := '0';             --  rotate_left.export
			rotate_right_export : in    std_logic                     := '0';  
			hex7_export         : out   std_logic_vector(6 downto 0);                     --         hex7.export
			hex_0_export        : out   std_logic_vector(6 downto 0);                     --        hex_0.export
			hex_1_export        : out   std_logic_vector(6 downto 0);                     --        hex_1.export
			hex_2_export        : out   std_logic_vector(6 downto 0);                     --        hex_2.export
			hex_3_export        : out   std_logic_vector(6 downto 0);                     --        hex_3.export
			hex_4_export        : out   std_logic_vector(6 downto 0);                     --        hex_4.export
			hex_5_export        : out   std_logic_vector(6 downto 0);                     --        hex_5.export
			hex_6_export        : out   std_logic_vector(6 downto 0);                     
			row_0_export  : out   std_logic_vector(29 downto 0);                    --  row_0.export
			row_1_export  : out   std_logic_vector(29 downto 0);                    --  row_1.export
			row_10_export : out   std_logic_vector(29 downto 0);                    -- row_10.export
			row_11_export : out   std_logic_vector(29 downto 0);                    -- row_11.export
			row_12_export : out   std_logic_vector(29 downto 0);                    -- row_12.export
			row_13_export : out   std_logic_vector(29 downto 0);                    -- row_13.export
			row_14_export : out   std_logic_vector(29 downto 0);                    -- row_14.export
			row_15_export : out   std_logic_vector(29 downto 0);                    -- row_15.export
			row_16_export : out   std_logic_vector(29 downto 0);                    -- row_16.export
			row_17_export : out   std_logic_vector(29 downto 0);                    -- row_17.export
			row_18_export : out   std_logic_vector(29 downto 0);                    -- row_18.export
			row_19_export : out   std_logic_vector(29 downto 0);                    -- row_19.export
			row_2_export  : out   std_logic_vector(29 downto 0);                    --  row_2.export
			row_20_export : out   std_logic_vector(29 downto 0);                    -- row_20.export
			row_21_export : out   std_logic_vector(29 downto 0);                    -- row_21.export
			row_22_export : out   std_logic_vector(29 downto 0);                    -- row_22.export
			row_23_export : out   std_logic_vector(29 downto 0);                    -- row_23.export
			row_3_export  : out   std_logic_vector(29 downto 0);                    --  row_3.export
			row_4_export  : out   std_logic_vector(29 downto 0);                    --  row_4.export
			row_5_export  : out   std_logic_vector(29 downto 0);                    --  row_5.export
			row_6_export  : out   std_logic_vector(29 downto 0);                    --  row_6.export
			row_7_export  : out   std_logic_vector(29 downto 0);                    --  row_7.export
			row_8_export  : out   std_logic_vector(29 downto 0);                    --  row_8.export
			row_9_export  : out   std_logic_vector(29 downto 0)
		);
	END COMPONENT;
	
	signal row: integer;
	signal column: integer;
	signal pixel_clk: std_logic;
	signal disp_ena: std_logic;
	signal grid: std_logic_vector(719 downto 0);
	signal test_grid: std_logic_vector(719 downto 0);
begin 
	test_grid(719 downto 717) <= "001";
	LEDR <= grid(29 downto 12);
	VGA_CLK <= pixel_clk;
	
	 NiosII : sram PORT MAP(
		 clk_clk => CLOCK_50,
		 reset_reset_n => '1',
		 move_left_export => KEY(3),
		 move_right_export => KEY(2),
		 rotate_left_export => KEY(1),
		 rotate_right_export => KEY(0),
		 row_0_export => grid(719 downto 690),
		 row_1_export => grid(689 downto 660), 
		 row_2_export => grid(659 downto 630),
		 row_3_export => grid(629 downto 600),
		 row_4_export => grid(599 downto 570),
		 row_5_export => grid(569 downto 540),
		 row_6_export => grid(539 downto 510), 
		 row_7_export => grid(509 downto 480),
		 row_8_export => grid(479 downto 450),
		 row_9_export => grid(449 downto 420),
		 row_10_export => grid(419 downto 390),
		 row_11_export => grid(389 downto 360),
		 row_12_export => grid(359 downto 330),
		 row_13_export => grid(329 downto 300),
		 row_14_export => grid(299 downto 270),
		 row_15_export => grid(269 downto 240),
		 row_16_export => grid(239 downto 210),
		 row_17_export => grid(209 downto 180),
		 row_18_export => grid(179 downto 150),
		 row_19_export => grid(149 downto 120),
		 row_20_export => grid(119 downto 90),
		 row_21_export => grid(89 downto 60),
		 row_22_export => grid(59 downto 30),
		 row_23_export => grid(29 downto 0),
		 hex7_export => HEX7,
		 hex_0_export => HEX0,
		 hex_1_export => HEX1, 
		 hex_2_export => HEX2,
		 hex_3_export => HEX3,
		 hex_4_export => HEX4,
		 hex_5_export => HEX5,
		 hex_6_export => HEX6                  
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
		row => column,
		column => row,
		display => grid,
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