
module sram (
	clk_clk,
	reset_reset_n,
	sram_DQ,
	sram_ADDR,
	sram_LB_N,
	sram_UB_N,
	sram_CE_N,
	sram_OE_N,
	sram_WE_N,
	row_0_export,
	row_1_export,
	row_2_export,
	row_3_export,
	row_4_export,
	row_5_export,
	row_6_export,
	row_7_export,
	row_8_export,
	row_9_export,
	row_10_export,
	row_11_export,
	row_12_export,
	row_13_export,
	row_14_export,
	row_15_export,
	row_16_export,
	row_17_export,
	row_18_export,
	row_19_export,
	row_20_export,
	row_21_export,
	row_22_export,
	row_23_export);	

	input		clk_clk;
	input		reset_reset_n;
	inout	[15:0]	sram_DQ;
	output	[19:0]	sram_ADDR;
	output		sram_LB_N;
	output		sram_UB_N;
	output		sram_CE_N;
	output		sram_OE_N;
	output		sram_WE_N;
	output	[29:0]	row_0_export;
	output	[29:0]	row_1_export;
	output	[29:0]	row_2_export;
	output	[29:0]	row_3_export;
	output	[29:0]	row_4_export;
	output	[29:0]	row_5_export;
	output	[29:0]	row_6_export;
	output	[29:0]	row_7_export;
	output	[29:0]	row_8_export;
	output	[29:0]	row_9_export;
	output	[29:0]	row_10_export;
	output	[29:0]	row_11_export;
	output	[29:0]	row_12_export;
	output	[29:0]	row_13_export;
	output	[29:0]	row_14_export;
	output	[29:0]	row_15_export;
	output	[29:0]	row_16_export;
	output	[29:0]	row_17_export;
	output	[29:0]	row_18_export;
	output	[29:0]	row_19_export;
	output	[29:0]	row_20_export;
	output	[29:0]	row_21_export;
	output	[29:0]	row_22_export;
	output	[29:0]	row_23_export;
endmodule
