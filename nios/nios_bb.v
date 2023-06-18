
module nios (
	clk_clk,
	reset_reset_n,
	switches_export,
	leds_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[17:0]	switches_export;
	output	[17:0]	leds_export;
endmodule
