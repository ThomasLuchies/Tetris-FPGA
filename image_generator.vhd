--------------------------------------------------------------------------------
--
--   FileName:         image_generator.vhd
--   Dependencies:     none
--   Design Software:  Quartus II 64-bit Version 12.1 Build 177 SJ Full Version
--
--   HDL CODE IS PROVIDED "AS IS."  DIGI-KEY EXPRESSLY DISCLAIMS ANY
--   WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
--   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
--   PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL DIGI-KEY
--   BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
--   DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
--   PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
--   BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
--   ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
--
--   Version History
--   Version 1.0 05/10/2013 Scott Larson
--     Initial Public Release
--    
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

ENTITY image_generator IS
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
		LEDG : out std_logic_vector(7 downto 0);
		
		-- SRAM
		data : inout std_logic_vector(15 downto 0);
		address : out std_logic_vector(19 downto 0);
		output_enable_n : out std_logic := '1';
		write_enable_n : buffer std_logic := '1';
		chip_select_n : out std_logic := '1';
		ub_n : out std_logic := '0'; -- always active
		lb_n : out std_logic := '0'); -- always active
END image_generator;

ARCHITECTURE behavior OF image_generator IS
	component prescaler is
		port( clki: in std_logic;
				factor: in integer;
				clko: out std_logic
			);
	end component;
	
	component sram_controller is 
		generic 
		(
			amount_of_adresses: unsigned(19 downto 0) := (others=>'1')
		);
		port
		(
			clk : in std_logic; -- assumes a speed of 50mHz

			-- user side
			read_n, write_n, clear_sram : in std_logic;
			data_input : in std_logic_vector(15 downto 0);
			addr_input : in std_logic_vector(19 downto 0);
			data_output : out std_logic_vector(15 downto 0);
			clear_done: out std_logic;

			
			-- SRAM side
			data : inout std_logic_vector(15 downto 0);
			address : out std_logic_vector(19 downto 0);
			output_enable_n : out std_logic := '1';
			write_enable_n : buffer std_logic := '1';
			chip_select_n : out std_logic := '1';
			ub_n : out std_logic := '0'; -- always active
			lb_n : out std_logic := '0' -- always active
		);
	end component;
	
	signal frame_clk: std_logic;
	signal prescale_factor: integer;
	signal frame: std_logic_vector(19 downto 0);
	signal clear_done: std_logic;
	signal read_n: std_logic := '0';
	signal sram_out: std_logic_vector(15 downto 0);
BEGIN
	
	prescale_factor <= 50_000_000 / 120;
	-- 50 mhz clock convert to 60 hz
	clk60: prescaler port map(clk, prescale_factor, frame_clk);
	sr: sram_controller port map(clk => clk,
										  read_n => read_n, 
										  write_n => '1', 
										  clear_sram =>'1', 
										  data_input =>"0000000000000000", 
										  addr_input =>"00000000000000000000", 
										  data_output => sram_out, 
										  clear_done => clear_done,
										  data => data,
										  address => address,
										  output_enable_n => output_enable_n,
										  write_enable_n => write_enable_n,
										  chip_select_n => chip_select_n,
										  ub_n => ub_n,
										  lb_n => lb_n);
   
	process(frame_clk)
		variable read_np: std_logic;
	begin
		if(rising_edge(frame_clk)) then
			read_np := not read_np;
		end if;
		
		read_n <= read_np;
	end process;
	
	PROCESS(disp_ena, row, column)
	BEGIN
		LEDG <= data(7 downto 0);
		IF(disp_ena = '1') THEN		--display time
			IF(row < pixels_y AND column < pixels_x) THEN
				if(row > 220 AND row < 440) then
					red <= "01000101";
					green <=  "01000100";
					blue <=  "01000011";
				else
					red <= "00000000";
					green <=  "00000000";
					blue <=  "00000000";
				end if;
			END IF;
		ELSE								--blanking time
			red <= (OTHERS => '0');
			green <= (OTHERS => '0');
			blue <= (OTHERS => '0');
		END IF;
	
	END PROCESS;
END behavior;