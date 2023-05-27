library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity prescaler is
	port( clki: in std_logic;
		factor: in integer;
		clko: out std_logic
		);
end entity;

architecture behaviour of prescaler is 
begin
	process(clki)
		variable cnt: integer;
		variable clko_p: std_logic;
	begin 
		if(rising_edge(clki)) then
			cnt := cnt + 1;
			if(cnt = factor) then
				clko_p := '1';
			else 
				clko_p := '0';
			end if;
		end if;
		
		clko <= clko_p;
	end process;
end architecture;