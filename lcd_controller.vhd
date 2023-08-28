-- LCD display controller for DE2-115

LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;


entity lcd_controller is
  port (
    CLOCK_50:     IN  STD_LOGIC;
	 reset_n: 			IN  STD_LOGIC;
	 
    LCD_DATA:     OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    LCD_RW:       OUT STD_LOGIC;	
	 LCD_EN:       OUT STD_LOGIC;
	 LCD_RS:       OUT STD_LOGIC;
    LCD_ON:       OUT STD_LOGIC);
end lcd_controller;


architecture FSMD OF lcd_controller is
	TYPE state_type is (s1,s2,s3,s4,s10,s11,s12,s13,s20,s21,s22,s23,s24);
	SIGNAL state: state_type;
	SIGNAL reset: std_logic;

	CONSTANT max:  INTEGER := 50000;
	CONSTANT half: INTEGER := max/2;
	SIGNAL clockticks: INTEGER RANGE 0 TO max;
	SIGNAL clock: STD_LOGIC;
	SIGNAL count: INTEGER;

	SUBTYPE ascii is STD_LOGIC_VECTOR(7 DOWNTO 0);
	TYPE charArray is array(1 to 16) OF ascii;
	TYPE initArray is array(1 to 7) OF ascii;
	-- LCD initialization sequence codes
	-- 0x38 init four times
	-- 0x06 Entry mode set: Increment One; No Shift
	-- 0x0F Display control: Display ON; Cursor ON; Blink ON
	-- 0x01 Display clear
	CONSTANT initcode: initArray := (x"38",x"38",x"38",x"38",x"06",x"0F",x"01");
	--                              P     a     u     l           V     e     l     d     h     u     i     j     z     e     n
   CONSTANT line1: charArray := (x"50",x"61",x"75",x"6C",x"20",x"56",x"65",x"6C",x"64",x"68",x"75",x"69",x"6A",x"7A",x"65",x"6E");
	--                                                            V     H     D     L    
	CONSTANT line2: charArray := (x"20",x"20",x"20",x"20",x"20",x"56",x"48",x"44",x"4c",x"20",x"20",x"20",x"20",x"20",x"20",x"20");

begin
	LCD_ON <= '1';
   reset <= reset; --press KEY0 to start (reset)
	
	lcd_control: process(clock, reset)
	begin
		if (reset = '1') then
			count <= 1;
			state <= s1;
		elsif rising_edge(clock) then
			CASE state is
			-- LCD initialization sequence
			-- The LCD_DATA is written to the LCD at the falling edge of the E line
			-- therefore we need to toggle the E line for each data write
			WHEN s1 =>
				LCD_DATA <= initcode(count);
				LCD_EN <= '1';
				LCD_RS <= '0';	-- RS=0; an instruction
				LCD_RW <= '0';	-- R/W'=0; write
				state <= s2;
			WHEN s2 =>
				LCD_EN <= '0';	-- set EN=0;
				count <= count + 1;
				if count + 1 <= 7 then
					state <= s1;
				else
					state <= s10;
				end if;

			-- move cursor to first line of display
			WHEN s10 =>
				LCD_DATA <= x"80";	-- x80 is address of 1st position on first line
				LCD_EN <= '1';
				LCD_RS <= '0';	-- RS=0; an instruction
				LCD_RW <= '0';	-- R/W'=0; write
				state <= s11;
			WHEN s11 =>
				LCD_EN <= '0';	-- toggle EN
				count <= 1;
				state <= s12;

			-- write 1st line text
			WHEN s12 =>
				LCD_DATA <= line1(count);
				LCD_EN <= '1';
				LCD_RS <= '1';	-- RS=1; data
				LCD_RW <= '0';	-- R/W'=0; write
				state <= s13;
			WHEN s13 =>
				LCD_EN <= '0';	-- toggle EN
				count <= count + 1;
				if count + 1 <= 16 then
					state <= s12;
				else
					state <= s20;
				end if;

			-- move cursor to second line of display
			WHEN s20 =>
				LCD_DATA <= x"BF";		-- xBF is address of 1st position on second line
				LCD_EN <= '1';
				LCD_RS <= '0';	-- RS=0; an instruction
				LCD_RW <= '0';	-- R/W'=0; write
				state <= s21;
			WHEN s21 =>
				LCD_EN <= '0';	-- toggle EN
				count <= 1;
				state <= s22;

			-- write 2nd line text
			WHEN s22 =>
				LCD_DATA <= line2(count);
				LCD_EN <= '1';	
				LCD_RS <= '1';	-- RS=1; data
				LCD_RW <= '0';	-- R/W'=0; write
				state <= s23;
			WHEN s23 =>
				LCD_EN <= '0';	-- set EN=0;
				count <= count + 1;
				if count + 1 <= 16 then
					state <= s22;
				else
					state <= s24;
				end if;
			WHEN s24 =>
				state <= s24;
			WHEN OTHERS =>
				state <= s24;
			end CASE;
		end if;
	end process;

	--make a 1KHz clock
	ClockDivide: process( CLOCK_50 )
	begin
		if ( rising_edge( CLOCK_50 )) then
		  if clockticks < max then
			  clockticks <= clockticks + 1;
		  else
			  clockticks <= 0;
		  end if;
		  if clockticks < half then
			  clock <= '0';
		  else
			  clock <= '1';
		  end if;
		end if;
	end process;

end FSMD;
