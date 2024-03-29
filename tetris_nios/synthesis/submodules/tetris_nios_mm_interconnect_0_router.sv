// (C) 2001-2018 Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License Subscription 
// Agreement, Intel FPGA IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Intel and sold by 
// Intel or its authorized distributors.  Please refer to the applicable 
// agreement for further details.



// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/18.1std/ip/merlin/altera_merlin_router/altera_merlin_router.sv.terp#1 $
// $Revision: #1 $
// $Date: 2018/07/18 $
// $Author: psgswbuild $

// -------------------------------------------------------
// Merlin Router
//
// Asserts the appropriate one-hot encoded channel based on 
// either (a) the address or (b) the dest id. The DECODER_TYPE
// parameter controls this behaviour. 0 means address decoder,
// 1 means dest id decoder.
//
// In the case of (a), it also sets the destination id.
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module tetris_nios_mm_interconnect_0_router_default_decode
  #(
     parameter DEFAULT_CHANNEL = 1,
               DEFAULT_WR_CHANNEL = -1,
               DEFAULT_RD_CHANNEL = -1,
               DEFAULT_DESTID = 42 
   )
  (output [94 - 89 : 0] default_destination_id,
   output [43-1 : 0] default_wr_channel,
   output [43-1 : 0] default_rd_channel,
   output [43-1 : 0] default_src_channel
  );

  assign default_destination_id = 
    DEFAULT_DESTID[94 - 89 : 0];

  generate
    if (DEFAULT_CHANNEL == -1) begin : no_default_channel_assignment
      assign default_src_channel = '0;
    end
    else begin : default_channel_assignment
      assign default_src_channel = 43'b1 << DEFAULT_CHANNEL;
    end
  endgenerate

  generate
    if (DEFAULT_RD_CHANNEL == -1) begin : no_default_rw_channel_assignment
      assign default_wr_channel = '0;
      assign default_rd_channel = '0;
    end
    else begin : default_rw_channel_assignment
      assign default_wr_channel = 43'b1 << DEFAULT_WR_CHANNEL;
      assign default_rd_channel = 43'b1 << DEFAULT_RD_CHANNEL;
    end
  endgenerate

endmodule


module tetris_nios_mm_interconnect_0_router
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // Command Sink (Input)
    // -------------------
    input                       sink_valid,
    input  [108-1 : 0]    sink_data,
    input                       sink_startofpacket,
    input                       sink_endofpacket,
    output                      sink_ready,

    // -------------------
    // Command Source (Output)
    // -------------------
    output                          src_valid,
    output reg [108-1    : 0] src_data,
    output reg [43-1 : 0] src_channel,
    output                          src_startofpacket,
    output                          src_endofpacket,
    input                           src_ready
);

    // -------------------------------------------------------
    // Local parameters and variables
    // -------------------------------------------------------
    localparam PKT_ADDR_H = 61;
    localparam PKT_ADDR_L = 36;
    localparam PKT_DEST_ID_H = 94;
    localparam PKT_DEST_ID_L = 89;
    localparam PKT_PROTECTION_H = 98;
    localparam PKT_PROTECTION_L = 96;
    localparam ST_DATA_W = 108;
    localparam ST_CHANNEL_W = 43;
    localparam DECODER_TYPE = 0;

    localparam PKT_TRANS_WRITE = 64;
    localparam PKT_TRANS_READ  = 65;

    localparam PKT_ADDR_W = PKT_ADDR_H-PKT_ADDR_L + 1;
    localparam PKT_DEST_ID_W = PKT_DEST_ID_H-PKT_DEST_ID_L + 1;



    // -------------------------------------------------------
    // Figure out the number of bits to mask off for each slave span
    // during address decoding
    // -------------------------------------------------------
    localparam PAD0 = log2ceil(64'h200000 - 64'h0); 
    localparam PAD1 = log2ceil(64'h240000 - 64'h200000); 
    localparam PAD2 = log2ceil(64'h240008 - 64'h240000); 
    localparam PAD3 = log2ceil(64'h241000 - 64'h240800); 
    localparam PAD4 = log2ceil(64'h250010 - 64'h250000); 
    localparam PAD5 = log2ceil(64'h2500020 - 64'h2500010); 
    localparam PAD6 = log2ceil(64'h2500030 - 64'h2500020); 
    localparam PAD7 = log2ceil(64'h2500040 - 64'h2500030); 
    localparam PAD8 = log2ceil(64'h2500050 - 64'h2500040); 
    localparam PAD9 = log2ceil(64'h2500060 - 64'h2500050); 
    localparam PAD10 = log2ceil(64'h2500070 - 64'h2500060); 
    localparam PAD11 = log2ceil(64'h2500080 - 64'h2500070); 
    localparam PAD12 = log2ceil(64'h2500090 - 64'h2500080); 
    localparam PAD13 = log2ceil(64'h25000a0 - 64'h2500090); 
    localparam PAD14 = log2ceil(64'h25000b0 - 64'h25000a0); 
    localparam PAD15 = log2ceil(64'h25000c0 - 64'h25000b0); 
    localparam PAD16 = log2ceil(64'h25000d0 - 64'h25000c0); 
    localparam PAD17 = log2ceil(64'h25000e0 - 64'h25000d0); 
    localparam PAD18 = log2ceil(64'h25000f0 - 64'h25000e0); 
    localparam PAD19 = log2ceil(64'h2500100 - 64'h25000f0); 
    localparam PAD20 = log2ceil(64'h2500110 - 64'h2500100); 
    localparam PAD21 = log2ceil(64'h2500120 - 64'h2500110); 
    localparam PAD22 = log2ceil(64'h2500130 - 64'h2500120); 
    localparam PAD23 = log2ceil(64'h2500140 - 64'h2500130); 
    localparam PAD24 = log2ceil(64'h2500150 - 64'h2500140); 
    localparam PAD25 = log2ceil(64'h2500160 - 64'h2500150); 
    localparam PAD26 = log2ceil(64'h2500170 - 64'h2500160); 
    localparam PAD27 = log2ceil(64'h2500180 - 64'h2500170); 
    localparam PAD28 = log2ceil(64'h2500190 - 64'h2500180); 
    localparam PAD29 = log2ceil(64'h25001a0 - 64'h2500190); 
    localparam PAD30 = log2ceil(64'h2500210 - 64'h2500200); 
    localparam PAD31 = log2ceil(64'h2500220 - 64'h2500210); 
    localparam PAD32 = log2ceil(64'h2500240 - 64'h2500220); 
    localparam PAD33 = log2ceil(64'h2500250 - 64'h2500240); 
    localparam PAD34 = log2ceil(64'h2500260 - 64'h2500250); 
    localparam PAD35 = log2ceil(64'h2500270 - 64'h2500260); 
    localparam PAD36 = log2ceil(64'h2500280 - 64'h2500270); 
    localparam PAD37 = log2ceil(64'h2500290 - 64'h2500280); 
    localparam PAD38 = log2ceil(64'h25002a0 - 64'h2500290); 
    localparam PAD39 = log2ceil(64'h2500310 - 64'h2500300); 
    localparam PAD40 = log2ceil(64'h2500320 - 64'h2500310); 
    localparam PAD41 = log2ceil(64'h2500330 - 64'h2500320); 
    localparam PAD42 = log2ceil(64'h2500340 - 64'h2500330); 
    // -------------------------------------------------------
    // Work out which address bits are significant based on the
    // address range of the slaves. If the required width is too
    // large or too small, we use the address field width instead.
    // -------------------------------------------------------
    localparam ADDR_RANGE = 64'h2500340;
    localparam RANGE_ADDR_WIDTH = log2ceil(ADDR_RANGE);
    localparam OPTIMIZED_ADDR_H = (RANGE_ADDR_WIDTH > PKT_ADDR_W) ||
                                  (RANGE_ADDR_WIDTH == 0) ?
                                        PKT_ADDR_H :
                                        PKT_ADDR_L + RANGE_ADDR_WIDTH - 1;

    localparam RG = RANGE_ADDR_WIDTH-1;
    localparam REAL_ADDRESS_RANGE = OPTIMIZED_ADDR_H - PKT_ADDR_L;

      reg [PKT_ADDR_W-1 : 0] address;
      always @* begin
        address = {PKT_ADDR_W{1'b0}};
        address [REAL_ADDRESS_RANGE:0] = sink_data[OPTIMIZED_ADDR_H : PKT_ADDR_L];
      end   

    // -------------------------------------------------------
    // Pass almost everything through, untouched
    // -------------------------------------------------------
    assign sink_ready        = src_ready;
    assign src_valid         = sink_valid;
    assign src_startofpacket = sink_startofpacket;
    assign src_endofpacket   = sink_endofpacket;
    wire [PKT_DEST_ID_W-1:0] default_destid;
    wire [43-1 : 0] default_src_channel;




    // -------------------------------------------------------
    // Write and read transaction signals
    // -------------------------------------------------------
    wire read_transaction;
    assign read_transaction  = sink_data[PKT_TRANS_READ];


    tetris_nios_mm_interconnect_0_router_default_decode the_default_decode(
      .default_destination_id (default_destid),
      .default_wr_channel   (),
      .default_rd_channel   (),
      .default_src_channel  (default_src_channel)
    );

    always @* begin
        src_data    = sink_data;
        src_channel = default_src_channel;
        src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = default_destid;

        // --------------------------------------------------
        // Address Decoder
        // Sets the channel and destination ID based on the address
        // --------------------------------------------------

    // ( 0x0 .. 0x200000 )
    if ( {address[RG:PAD0],{PAD0{1'b0}}} == 26'h0   ) begin
            src_channel = 43'b0000000000000000000000000000000000000000010;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 42;
    end

    // ( 0x200000 .. 0x240000 )
    if ( {address[RG:PAD1],{PAD1{1'b0}}} == 26'h200000   ) begin
            src_channel = 43'b0000000000000000000000000000000000000001000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 14;
    end

    // ( 0x240000 .. 0x240008 )
    if ( {address[RG:PAD2],{PAD2{1'b0}}} == 26'h240000   ) begin
            src_channel = 43'b0000000000000000000000000000000000000000001;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 10;
    end

    // ( 0x240800 .. 0x241000 )
    if ( {address[RG:PAD3],{PAD3{1'b0}}} == 26'h240800   ) begin
            src_channel = 43'b0000000000000000000000000000000000000000100;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 13;
    end

    // ( 0x250000 .. 0x250010 )
    if ( {address[RG:PAD4],{PAD4{1'b0}}} == 26'h250000   ) begin
            src_channel = 43'b0000000000000000000000000000000000000010000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 18;
    end

    // ( 0x2500010 .. 0x2500020 )
    if ( {address[RG:PAD5],{PAD5{1'b0}}} == 26'h2500010   ) begin
            src_channel = 43'b0000000000000000000000000000000000000100000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 29;
    end

    // ( 0x2500020 .. 0x2500030 )
    if ( {address[RG:PAD6],{PAD6{1'b0}}} == 26'h2500020   ) begin
            src_channel = 43'b0000000000000000000000000000000000001000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 34;
    end

    // ( 0x2500030 .. 0x2500040 )
    if ( {address[RG:PAD7],{PAD7{1'b0}}} == 26'h2500030   ) begin
            src_channel = 43'b0000000000000000000000000000000000010000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 35;
    end

    // ( 0x2500040 .. 0x2500050 )
    if ( {address[RG:PAD8],{PAD8{1'b0}}} == 26'h2500040   ) begin
            src_channel = 43'b0000000000000000000000000000000000100000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 36;
    end

    // ( 0x2500050 .. 0x2500060 )
    if ( {address[RG:PAD9],{PAD9{1'b0}}} == 26'h2500050   ) begin
            src_channel = 43'b0000000000000000000000000000000001000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 37;
    end

    // ( 0x2500060 .. 0x2500070 )
    if ( {address[RG:PAD10],{PAD10{1'b0}}} == 26'h2500060   ) begin
            src_channel = 43'b0000000000000000000000000000000010000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 38;
    end

    // ( 0x2500070 .. 0x2500080 )
    if ( {address[RG:PAD11],{PAD11{1'b0}}} == 26'h2500070   ) begin
            src_channel = 43'b0000000000000000000000000000000100000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 39;
    end

    // ( 0x2500080 .. 0x2500090 )
    if ( {address[RG:PAD12],{PAD12{1'b0}}} == 26'h2500080   ) begin
            src_channel = 43'b0000000000000000000000000000001000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 40;
    end

    // ( 0x2500090 .. 0x25000a0 )
    if ( {address[RG:PAD13],{PAD13{1'b0}}} == 26'h2500090   ) begin
            src_channel = 43'b0000000000000000000000000000010000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 41;
    end

    // ( 0x25000a0 .. 0x25000b0 )
    if ( {address[RG:PAD14],{PAD14{1'b0}}} == 26'h25000a0   ) begin
            src_channel = 43'b0000000000000001000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 19;
    end

    // ( 0x25000b0 .. 0x25000c0 )
    if ( {address[RG:PAD15],{PAD15{1'b0}}} == 26'h25000b0   ) begin
            src_channel = 43'b0000000000000000000000000000100000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 20;
    end

    // ( 0x25000c0 .. 0x25000d0 )
    if ( {address[RG:PAD16],{PAD16{1'b0}}} == 26'h25000c0   ) begin
            src_channel = 43'b0000000000000000000000000001000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 21;
    end

    // ( 0x25000d0 .. 0x25000e0 )
    if ( {address[RG:PAD17],{PAD17{1'b0}}} == 26'h25000d0   ) begin
            src_channel = 43'b0000000000000000000000000010000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 22;
    end

    // ( 0x25000e0 .. 0x25000f0 )
    if ( {address[RG:PAD18],{PAD18{1'b0}}} == 26'h25000e0   ) begin
            src_channel = 43'b0000000000000000000000000100000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 23;
    end

    // ( 0x25000f0 .. 0x2500100 )
    if ( {address[RG:PAD19],{PAD19{1'b0}}} == 26'h25000f0   ) begin
            src_channel = 43'b0000000000000000000000001000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 24;
    end

    // ( 0x2500100 .. 0x2500110 )
    if ( {address[RG:PAD20],{PAD20{1'b0}}} == 26'h2500100   ) begin
            src_channel = 43'b0000000000000000000000010000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 25;
    end

    // ( 0x2500110 .. 0x2500120 )
    if ( {address[RG:PAD21],{PAD21{1'b0}}} == 26'h2500110   ) begin
            src_channel = 43'b0000000000000000000000100000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 26;
    end

    // ( 0x2500120 .. 0x2500130 )
    if ( {address[RG:PAD22],{PAD22{1'b0}}} == 26'h2500120   ) begin
            src_channel = 43'b0000000000000000000001000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 27;
    end

    // ( 0x2500130 .. 0x2500140 )
    if ( {address[RG:PAD23],{PAD23{1'b0}}} == 26'h2500130   ) begin
            src_channel = 43'b0000000000000000000010000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 28;
    end

    // ( 0x2500140 .. 0x2500150 )
    if ( {address[RG:PAD24],{PAD24{1'b0}}} == 26'h2500140   ) begin
            src_channel = 43'b0000000000000000000100000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 30;
    end

    // ( 0x2500150 .. 0x2500160 )
    if ( {address[RG:PAD25],{PAD25{1'b0}}} == 26'h2500150   ) begin
            src_channel = 43'b0000000000000000001000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 31;
    end

    // ( 0x2500160 .. 0x2500170 )
    if ( {address[RG:PAD26],{PAD26{1'b0}}} == 26'h2500160   ) begin
            src_channel = 43'b0000000000000000010000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 32;
    end

    // ( 0x2500170 .. 0x2500180 )
    if ( {address[RG:PAD27],{PAD27{1'b0}}} == 26'h2500170   ) begin
            src_channel = 43'b0000000000000000100000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 33;
    end

    // ( 0x2500180 .. 0x2500190 )
    if ( {address[RG:PAD28],{PAD28{1'b0}}} == 26'h2500180   ) begin
            src_channel = 43'b0000000000000010000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 11;
    end

    // ( 0x2500190 .. 0x25001a0 )
    if ( {address[RG:PAD29],{PAD29{1'b0}}} == 26'h2500190   ) begin
            src_channel = 43'b0000000000000100000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 12;
    end

    // ( 0x2500200 .. 0x2500210 )
    if ( {address[RG:PAD30],{PAD30{1'b0}}} == 26'h2500200   ) begin
            src_channel = 43'b0000000000001000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 16;
    end

    // ( 0x2500210 .. 0x2500220 )
    if ( {address[RG:PAD31],{PAD31{1'b0}}} == 26'h2500210   ) begin
            src_channel = 43'b0000000000010000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 17;
    end

    // ( 0x2500220 .. 0x2500240 )
    if ( {address[RG:PAD32],{PAD32{1'b0}}} == 26'h2500220   ) begin
            src_channel = 43'b0000000000100000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 9;
    end

    // ( 0x2500240 .. 0x2500250 )
    if ( {address[RG:PAD33],{PAD33{1'b0}}} == 26'h2500240   ) begin
            src_channel = 43'b0000000001000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 0;
    end

    // ( 0x2500250 .. 0x2500260 )
    if ( {address[RG:PAD34],{PAD34{1'b0}}} == 26'h2500250   ) begin
            src_channel = 43'b0000000010000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 1;
    end

    // ( 0x2500260 .. 0x2500270 )
    if ( {address[RG:PAD35],{PAD35{1'b0}}} == 26'h2500260   ) begin
            src_channel = 43'b0000000100000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 2;
    end

    // ( 0x2500270 .. 0x2500280 )
    if ( {address[RG:PAD36],{PAD36{1'b0}}} == 26'h2500270   ) begin
            src_channel = 43'b0000001000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 3;
    end

    // ( 0x2500280 .. 0x2500290 )
    if ( {address[RG:PAD37],{PAD37{1'b0}}} == 26'h2500280   ) begin
            src_channel = 43'b0000010000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 4;
    end

    // ( 0x2500290 .. 0x25002a0 )
    if ( {address[RG:PAD38],{PAD38{1'b0}}} == 26'h2500290   ) begin
            src_channel = 43'b0000100000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 5;
    end

    // ( 0x2500300 .. 0x2500310 )
    if ( {address[RG:PAD39],{PAD39{1'b0}}} == 26'h2500300   ) begin
            src_channel = 43'b0001000000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 6;
    end

    // ( 0x2500310 .. 0x2500320 )
    if ( {address[RG:PAD40],{PAD40{1'b0}}} == 26'h2500310   ) begin
            src_channel = 43'b0010000000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 7;
    end

    // ( 0x2500320 .. 0x2500330 )
    if ( {address[RG:PAD41],{PAD41{1'b0}}} == 26'h2500320  && read_transaction  ) begin
            src_channel = 43'b0100000000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 15;
    end

    // ( 0x2500330 .. 0x2500340 )
    if ( {address[RG:PAD42],{PAD42{1'b0}}} == 26'h2500330  && read_transaction  ) begin
            src_channel = 43'b1000000000000000000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 8;
    end

end


    // --------------------------------------------------
    // Ceil(log2()) function
    // --------------------------------------------------
    function integer log2ceil;
        input reg[65:0] val;
        reg [65:0] i;

        begin
            i = 1;
            log2ceil = 0;

            while (i < val) begin
                log2ceil = log2ceil + 1;
                i = i << 1;
            end
        end
    endfunction

endmodule


