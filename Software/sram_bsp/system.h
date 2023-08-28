/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'sram'
 * SOPC Builder design path: ../../sram.sopcinfo
 *
 * Generated: Mon Aug 28 21:16:47 CEST 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00240820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1a
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00200020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x16
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00200000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00240820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1a
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00200020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x16
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00200000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_SRAM


/*
 * HEX_0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_0 altera_avalon_pio
#define HEX_0_BASE 0x2500240
#define HEX_0_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_0_CAPTURE 0
#define HEX_0_DATA_WIDTH 7
#define HEX_0_DO_TEST_BENCH_WIRING 0
#define HEX_0_DRIVEN_SIM_VALUE 0
#define HEX_0_EDGE_TYPE "NONE"
#define HEX_0_FREQ 50000000
#define HEX_0_HAS_IN 0
#define HEX_0_HAS_OUT 1
#define HEX_0_HAS_TRI 0
#define HEX_0_IRQ -1
#define HEX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_0_IRQ_TYPE "NONE"
#define HEX_0_NAME "/dev/HEX_0"
#define HEX_0_RESET_VALUE 0
#define HEX_0_SPAN 16
#define HEX_0_TYPE "altera_avalon_pio"


/*
 * HEX_1 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_1 altera_avalon_pio
#define HEX_1_BASE 0x2500250
#define HEX_1_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_1_CAPTURE 0
#define HEX_1_DATA_WIDTH 7
#define HEX_1_DO_TEST_BENCH_WIRING 0
#define HEX_1_DRIVEN_SIM_VALUE 0
#define HEX_1_EDGE_TYPE "NONE"
#define HEX_1_FREQ 50000000
#define HEX_1_HAS_IN 0
#define HEX_1_HAS_OUT 1
#define HEX_1_HAS_TRI 0
#define HEX_1_IRQ -1
#define HEX_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_1_IRQ_TYPE "NONE"
#define HEX_1_NAME "/dev/HEX_1"
#define HEX_1_RESET_VALUE 0
#define HEX_1_SPAN 16
#define HEX_1_TYPE "altera_avalon_pio"


/*
 * HEX_2 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_2 altera_avalon_pio
#define HEX_2_BASE 0x2500260
#define HEX_2_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_2_CAPTURE 0
#define HEX_2_DATA_WIDTH 7
#define HEX_2_DO_TEST_BENCH_WIRING 0
#define HEX_2_DRIVEN_SIM_VALUE 0
#define HEX_2_EDGE_TYPE "NONE"
#define HEX_2_FREQ 50000000
#define HEX_2_HAS_IN 0
#define HEX_2_HAS_OUT 1
#define HEX_2_HAS_TRI 0
#define HEX_2_IRQ -1
#define HEX_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_2_IRQ_TYPE "NONE"
#define HEX_2_NAME "/dev/HEX_2"
#define HEX_2_RESET_VALUE 0
#define HEX_2_SPAN 16
#define HEX_2_TYPE "altera_avalon_pio"


/*
 * HEX_3 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_3 altera_avalon_pio
#define HEX_3_BASE 0x2500270
#define HEX_3_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_3_CAPTURE 0
#define HEX_3_DATA_WIDTH 7
#define HEX_3_DO_TEST_BENCH_WIRING 0
#define HEX_3_DRIVEN_SIM_VALUE 0
#define HEX_3_EDGE_TYPE "NONE"
#define HEX_3_FREQ 50000000
#define HEX_3_HAS_IN 0
#define HEX_3_HAS_OUT 1
#define HEX_3_HAS_TRI 0
#define HEX_3_IRQ -1
#define HEX_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_3_IRQ_TYPE "NONE"
#define HEX_3_NAME "/dev/HEX_3"
#define HEX_3_RESET_VALUE 0
#define HEX_3_SPAN 16
#define HEX_3_TYPE "altera_avalon_pio"


/*
 * HEX_4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_4 altera_avalon_pio
#define HEX_4_BASE 0x2500280
#define HEX_4_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_4_CAPTURE 0
#define HEX_4_DATA_WIDTH 7
#define HEX_4_DO_TEST_BENCH_WIRING 0
#define HEX_4_DRIVEN_SIM_VALUE 0
#define HEX_4_EDGE_TYPE "NONE"
#define HEX_4_FREQ 50000000
#define HEX_4_HAS_IN 0
#define HEX_4_HAS_OUT 1
#define HEX_4_HAS_TRI 0
#define HEX_4_IRQ -1
#define HEX_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_4_IRQ_TYPE "NONE"
#define HEX_4_NAME "/dev/HEX_4"
#define HEX_4_RESET_VALUE 0
#define HEX_4_SPAN 16
#define HEX_4_TYPE "altera_avalon_pio"


/*
 * HEX_5 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_5 altera_avalon_pio
#define HEX_5_BASE 0x2500290
#define HEX_5_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_5_CAPTURE 0
#define HEX_5_DATA_WIDTH 7
#define HEX_5_DO_TEST_BENCH_WIRING 0
#define HEX_5_DRIVEN_SIM_VALUE 0
#define HEX_5_EDGE_TYPE "NONE"
#define HEX_5_FREQ 50000000
#define HEX_5_HAS_IN 0
#define HEX_5_HAS_OUT 1
#define HEX_5_HAS_TRI 0
#define HEX_5_IRQ -1
#define HEX_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_5_IRQ_TYPE "NONE"
#define HEX_5_NAME "/dev/HEX_5"
#define HEX_5_RESET_VALUE 0
#define HEX_5_SPAN 16
#define HEX_5_TYPE "altera_avalon_pio"


/*
 * HEX_6 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_6 altera_avalon_pio
#define HEX_6_BASE 0x2500300
#define HEX_6_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_6_CAPTURE 0
#define HEX_6_DATA_WIDTH 7
#define HEX_6_DO_TEST_BENCH_WIRING 0
#define HEX_6_DRIVEN_SIM_VALUE 0
#define HEX_6_EDGE_TYPE "NONE"
#define HEX_6_FREQ 50000000
#define HEX_6_HAS_IN 0
#define HEX_6_HAS_OUT 1
#define HEX_6_HAS_TRI 0
#define HEX_6_IRQ -1
#define HEX_6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_6_IRQ_TYPE "NONE"
#define HEX_6_NAME "/dev/HEX_6"
#define HEX_6_RESET_VALUE 0
#define HEX_6_SPAN 16
#define HEX_6_TYPE "altera_avalon_pio"


/*
 * HEX_7 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX_7 altera_avalon_pio
#define HEX_7_BASE 0x2500310
#define HEX_7_BIT_CLEARING_EDGE_REGISTER 0
#define HEX_7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX_7_CAPTURE 0
#define HEX_7_DATA_WIDTH 7
#define HEX_7_DO_TEST_BENCH_WIRING 0
#define HEX_7_DRIVEN_SIM_VALUE 0
#define HEX_7_EDGE_TYPE "NONE"
#define HEX_7_FREQ 50000000
#define HEX_7_HAS_IN 0
#define HEX_7_HAS_OUT 1
#define HEX_7_HAS_TRI 0
#define HEX_7_IRQ -1
#define HEX_7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX_7_IRQ_TYPE "NONE"
#define HEX_7_NAME "/dev/HEX_7"
#define HEX_7_RESET_VALUE 0
#define HEX_7_SPAN 16
#define HEX_7_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x240000
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x240000
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x240000
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "sram"


/*
 * frame_timer configuration
 *
 */

#define ALT_MODULE_CLASS_frame_timer altera_avalon_timer
#define FRAME_TIMER_ALWAYS_RUN 0
#define FRAME_TIMER_BASE 0x2500220
#define FRAME_TIMER_COUNTER_SIZE 32
#define FRAME_TIMER_FIXED_PERIOD 0
#define FRAME_TIMER_FREQ 50000000
#define FRAME_TIMER_IRQ 5
#define FRAME_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FRAME_TIMER_LOAD_VALUE 834999
#define FRAME_TIMER_MULT 0.001
#define FRAME_TIMER_NAME "/dev/frame_timer"
#define FRAME_TIMER_PERIOD 16.7
#define FRAME_TIMER_PERIOD_UNITS "ms"
#define FRAME_TIMER_RESET_OUTPUT 0
#define FRAME_TIMER_SNAPSHOT 1
#define FRAME_TIMER_SPAN 32
#define FRAME_TIMER_TICKS_PER_SEC 59
#define FRAME_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define FRAME_TIMER_TYPE "altera_avalon_timer"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x240000
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * move_left configuration
 *
 */

#define ALT_MODULE_CLASS_move_left altera_avalon_pio
#define MOVE_LEFT_BASE 0x2500180
#define MOVE_LEFT_BIT_CLEARING_EDGE_REGISTER 0
#define MOVE_LEFT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MOVE_LEFT_CAPTURE 1
#define MOVE_LEFT_DATA_WIDTH 1
#define MOVE_LEFT_DO_TEST_BENCH_WIRING 0
#define MOVE_LEFT_DRIVEN_SIM_VALUE 0
#define MOVE_LEFT_EDGE_TYPE "FALLING"
#define MOVE_LEFT_FREQ 50000000
#define MOVE_LEFT_HAS_IN 1
#define MOVE_LEFT_HAS_OUT 0
#define MOVE_LEFT_HAS_TRI 0
#define MOVE_LEFT_IRQ 1
#define MOVE_LEFT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define MOVE_LEFT_IRQ_TYPE "EDGE"
#define MOVE_LEFT_NAME "/dev/move_left"
#define MOVE_LEFT_RESET_VALUE 0
#define MOVE_LEFT_SPAN 16
#define MOVE_LEFT_TYPE "altera_avalon_pio"


/*
 * move_right configuration
 *
 */

#define ALT_MODULE_CLASS_move_right altera_avalon_pio
#define MOVE_RIGHT_BASE 0x2500190
#define MOVE_RIGHT_BIT_CLEARING_EDGE_REGISTER 0
#define MOVE_RIGHT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MOVE_RIGHT_CAPTURE 1
#define MOVE_RIGHT_DATA_WIDTH 1
#define MOVE_RIGHT_DO_TEST_BENCH_WIRING 0
#define MOVE_RIGHT_DRIVEN_SIM_VALUE 0
#define MOVE_RIGHT_EDGE_TYPE "FALLING"
#define MOVE_RIGHT_FREQ 50000000
#define MOVE_RIGHT_HAS_IN 1
#define MOVE_RIGHT_HAS_OUT 0
#define MOVE_RIGHT_HAS_TRI 0
#define MOVE_RIGHT_IRQ 2
#define MOVE_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define MOVE_RIGHT_IRQ_TYPE "EDGE"
#define MOVE_RIGHT_NAME "/dev/move_right"
#define MOVE_RIGHT_RESET_VALUE 0
#define MOVE_RIGHT_SPAN 16
#define MOVE_RIGHT_TYPE "altera_avalon_pio"


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x200000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "sram_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 200096
#define ONCHIP_MEMORY2_0_SPAN 200096
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * rotate_left configuration
 *
 */

#define ALT_MODULE_CLASS_rotate_left altera_avalon_pio
#define ROTATE_LEFT_BASE 0x2500200
#define ROTATE_LEFT_BIT_CLEARING_EDGE_REGISTER 0
#define ROTATE_LEFT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROTATE_LEFT_CAPTURE 1
#define ROTATE_LEFT_DATA_WIDTH 1
#define ROTATE_LEFT_DO_TEST_BENCH_WIRING 0
#define ROTATE_LEFT_DRIVEN_SIM_VALUE 0
#define ROTATE_LEFT_EDGE_TYPE "FALLING"
#define ROTATE_LEFT_FREQ 50000000
#define ROTATE_LEFT_HAS_IN 1
#define ROTATE_LEFT_HAS_OUT 0
#define ROTATE_LEFT_HAS_TRI 0
#define ROTATE_LEFT_IRQ 3
#define ROTATE_LEFT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ROTATE_LEFT_IRQ_TYPE "EDGE"
#define ROTATE_LEFT_NAME "/dev/rotate_left"
#define ROTATE_LEFT_RESET_VALUE 0
#define ROTATE_LEFT_SPAN 16
#define ROTATE_LEFT_TYPE "altera_avalon_pio"


/*
 * rotate_right configuration
 *
 */

#define ALT_MODULE_CLASS_rotate_right altera_avalon_pio
#define ROTATE_RIGHT_BASE 0x2500210
#define ROTATE_RIGHT_BIT_CLEARING_EDGE_REGISTER 0
#define ROTATE_RIGHT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROTATE_RIGHT_CAPTURE 1
#define ROTATE_RIGHT_DATA_WIDTH 1
#define ROTATE_RIGHT_DO_TEST_BENCH_WIRING 0
#define ROTATE_RIGHT_DRIVEN_SIM_VALUE 0
#define ROTATE_RIGHT_EDGE_TYPE "FALLING"
#define ROTATE_RIGHT_FREQ 50000000
#define ROTATE_RIGHT_HAS_IN 1
#define ROTATE_RIGHT_HAS_OUT 0
#define ROTATE_RIGHT_HAS_TRI 0
#define ROTATE_RIGHT_IRQ 4
#define ROTATE_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ROTATE_RIGHT_IRQ_TYPE "EDGE"
#define ROTATE_RIGHT_NAME "/dev/rotate_right"
#define ROTATE_RIGHT_RESET_VALUE 0
#define ROTATE_RIGHT_SPAN 16
#define ROTATE_RIGHT_TYPE "altera_avalon_pio"


/*
 * row_0 configuration
 *
 */

#define ALT_MODULE_CLASS_row_0 altera_avalon_pio
#define ROW_0_BASE 0x250000
#define ROW_0_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_0_CAPTURE 0
#define ROW_0_DATA_WIDTH 30
#define ROW_0_DO_TEST_BENCH_WIRING 0
#define ROW_0_DRIVEN_SIM_VALUE 0
#define ROW_0_EDGE_TYPE "NONE"
#define ROW_0_FREQ 50000000
#define ROW_0_HAS_IN 0
#define ROW_0_HAS_OUT 1
#define ROW_0_HAS_TRI 0
#define ROW_0_IRQ -1
#define ROW_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_0_IRQ_TYPE "NONE"
#define ROW_0_NAME "/dev/row_0"
#define ROW_0_RESET_VALUE 0
#define ROW_0_SPAN 16
#define ROW_0_TYPE "altera_avalon_pio"


/*
 * row_1 configuration
 *
 */

#define ALT_MODULE_CLASS_row_1 altera_avalon_pio
#define ROW_1_BASE 0x2500010
#define ROW_1_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_1_CAPTURE 0
#define ROW_1_DATA_WIDTH 30
#define ROW_1_DO_TEST_BENCH_WIRING 0
#define ROW_1_DRIVEN_SIM_VALUE 0
#define ROW_1_EDGE_TYPE "NONE"
#define ROW_1_FREQ 50000000
#define ROW_1_HAS_IN 0
#define ROW_1_HAS_OUT 1
#define ROW_1_HAS_TRI 0
#define ROW_1_IRQ -1
#define ROW_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_1_IRQ_TYPE "NONE"
#define ROW_1_NAME "/dev/row_1"
#define ROW_1_RESET_VALUE 0
#define ROW_1_SPAN 16
#define ROW_1_TYPE "altera_avalon_pio"


/*
 * row_10 configuration
 *
 */

#define ALT_MODULE_CLASS_row_10 altera_avalon_pio
#define ROW_10_BASE 0x25000a0
#define ROW_10_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_10_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_10_CAPTURE 0
#define ROW_10_DATA_WIDTH 30
#define ROW_10_DO_TEST_BENCH_WIRING 0
#define ROW_10_DRIVEN_SIM_VALUE 0
#define ROW_10_EDGE_TYPE "NONE"
#define ROW_10_FREQ 50000000
#define ROW_10_HAS_IN 0
#define ROW_10_HAS_OUT 1
#define ROW_10_HAS_TRI 0
#define ROW_10_IRQ -1
#define ROW_10_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_10_IRQ_TYPE "NONE"
#define ROW_10_NAME "/dev/row_10"
#define ROW_10_RESET_VALUE 0
#define ROW_10_SPAN 16
#define ROW_10_TYPE "altera_avalon_pio"


/*
 * row_11 configuration
 *
 */

#define ALT_MODULE_CLASS_row_11 altera_avalon_pio
#define ROW_11_BASE 0x25000b0
#define ROW_11_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_11_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_11_CAPTURE 0
#define ROW_11_DATA_WIDTH 30
#define ROW_11_DO_TEST_BENCH_WIRING 0
#define ROW_11_DRIVEN_SIM_VALUE 0
#define ROW_11_EDGE_TYPE "NONE"
#define ROW_11_FREQ 50000000
#define ROW_11_HAS_IN 0
#define ROW_11_HAS_OUT 1
#define ROW_11_HAS_TRI 0
#define ROW_11_IRQ -1
#define ROW_11_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_11_IRQ_TYPE "NONE"
#define ROW_11_NAME "/dev/row_11"
#define ROW_11_RESET_VALUE 0
#define ROW_11_SPAN 16
#define ROW_11_TYPE "altera_avalon_pio"


/*
 * row_12 configuration
 *
 */

#define ALT_MODULE_CLASS_row_12 altera_avalon_pio
#define ROW_12_BASE 0x25000c0
#define ROW_12_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_12_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_12_CAPTURE 0
#define ROW_12_DATA_WIDTH 30
#define ROW_12_DO_TEST_BENCH_WIRING 0
#define ROW_12_DRIVEN_SIM_VALUE 0
#define ROW_12_EDGE_TYPE "NONE"
#define ROW_12_FREQ 50000000
#define ROW_12_HAS_IN 0
#define ROW_12_HAS_OUT 1
#define ROW_12_HAS_TRI 0
#define ROW_12_IRQ -1
#define ROW_12_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_12_IRQ_TYPE "NONE"
#define ROW_12_NAME "/dev/row_12"
#define ROW_12_RESET_VALUE 0
#define ROW_12_SPAN 16
#define ROW_12_TYPE "altera_avalon_pio"


/*
 * row_13 configuration
 *
 */

#define ALT_MODULE_CLASS_row_13 altera_avalon_pio
#define ROW_13_BASE 0x25000d0
#define ROW_13_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_13_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_13_CAPTURE 0
#define ROW_13_DATA_WIDTH 30
#define ROW_13_DO_TEST_BENCH_WIRING 0
#define ROW_13_DRIVEN_SIM_VALUE 0
#define ROW_13_EDGE_TYPE "NONE"
#define ROW_13_FREQ 50000000
#define ROW_13_HAS_IN 0
#define ROW_13_HAS_OUT 1
#define ROW_13_HAS_TRI 0
#define ROW_13_IRQ -1
#define ROW_13_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_13_IRQ_TYPE "NONE"
#define ROW_13_NAME "/dev/row_13"
#define ROW_13_RESET_VALUE 0
#define ROW_13_SPAN 16
#define ROW_13_TYPE "altera_avalon_pio"


/*
 * row_14 configuration
 *
 */

#define ALT_MODULE_CLASS_row_14 altera_avalon_pio
#define ROW_14_BASE 0x25000e0
#define ROW_14_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_14_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_14_CAPTURE 0
#define ROW_14_DATA_WIDTH 30
#define ROW_14_DO_TEST_BENCH_WIRING 0
#define ROW_14_DRIVEN_SIM_VALUE 0
#define ROW_14_EDGE_TYPE "NONE"
#define ROW_14_FREQ 50000000
#define ROW_14_HAS_IN 0
#define ROW_14_HAS_OUT 1
#define ROW_14_HAS_TRI 0
#define ROW_14_IRQ -1
#define ROW_14_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_14_IRQ_TYPE "NONE"
#define ROW_14_NAME "/dev/row_14"
#define ROW_14_RESET_VALUE 0
#define ROW_14_SPAN 16
#define ROW_14_TYPE "altera_avalon_pio"


/*
 * row_15 configuration
 *
 */

#define ALT_MODULE_CLASS_row_15 altera_avalon_pio
#define ROW_15_BASE 0x25000f0
#define ROW_15_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_15_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_15_CAPTURE 0
#define ROW_15_DATA_WIDTH 30
#define ROW_15_DO_TEST_BENCH_WIRING 0
#define ROW_15_DRIVEN_SIM_VALUE 0
#define ROW_15_EDGE_TYPE "NONE"
#define ROW_15_FREQ 50000000
#define ROW_15_HAS_IN 0
#define ROW_15_HAS_OUT 1
#define ROW_15_HAS_TRI 0
#define ROW_15_IRQ -1
#define ROW_15_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_15_IRQ_TYPE "NONE"
#define ROW_15_NAME "/dev/row_15"
#define ROW_15_RESET_VALUE 0
#define ROW_15_SPAN 16
#define ROW_15_TYPE "altera_avalon_pio"


/*
 * row_16 configuration
 *
 */

#define ALT_MODULE_CLASS_row_16 altera_avalon_pio
#define ROW_16_BASE 0x2500100
#define ROW_16_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_16_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_16_CAPTURE 0
#define ROW_16_DATA_WIDTH 30
#define ROW_16_DO_TEST_BENCH_WIRING 0
#define ROW_16_DRIVEN_SIM_VALUE 0
#define ROW_16_EDGE_TYPE "NONE"
#define ROW_16_FREQ 50000000
#define ROW_16_HAS_IN 0
#define ROW_16_HAS_OUT 1
#define ROW_16_HAS_TRI 0
#define ROW_16_IRQ -1
#define ROW_16_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_16_IRQ_TYPE "NONE"
#define ROW_16_NAME "/dev/row_16"
#define ROW_16_RESET_VALUE 0
#define ROW_16_SPAN 16
#define ROW_16_TYPE "altera_avalon_pio"


/*
 * row_17 configuration
 *
 */

#define ALT_MODULE_CLASS_row_17 altera_avalon_pio
#define ROW_17_BASE 0x2500110
#define ROW_17_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_17_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_17_CAPTURE 0
#define ROW_17_DATA_WIDTH 30
#define ROW_17_DO_TEST_BENCH_WIRING 0
#define ROW_17_DRIVEN_SIM_VALUE 0
#define ROW_17_EDGE_TYPE "NONE"
#define ROW_17_FREQ 50000000
#define ROW_17_HAS_IN 0
#define ROW_17_HAS_OUT 1
#define ROW_17_HAS_TRI 0
#define ROW_17_IRQ -1
#define ROW_17_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_17_IRQ_TYPE "NONE"
#define ROW_17_NAME "/dev/row_17"
#define ROW_17_RESET_VALUE 0
#define ROW_17_SPAN 16
#define ROW_17_TYPE "altera_avalon_pio"


/*
 * row_18 configuration
 *
 */

#define ALT_MODULE_CLASS_row_18 altera_avalon_pio
#define ROW_18_BASE 0x2500120
#define ROW_18_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_18_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_18_CAPTURE 0
#define ROW_18_DATA_WIDTH 30
#define ROW_18_DO_TEST_BENCH_WIRING 0
#define ROW_18_DRIVEN_SIM_VALUE 0
#define ROW_18_EDGE_TYPE "NONE"
#define ROW_18_FREQ 50000000
#define ROW_18_HAS_IN 0
#define ROW_18_HAS_OUT 1
#define ROW_18_HAS_TRI 0
#define ROW_18_IRQ -1
#define ROW_18_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_18_IRQ_TYPE "NONE"
#define ROW_18_NAME "/dev/row_18"
#define ROW_18_RESET_VALUE 0
#define ROW_18_SPAN 16
#define ROW_18_TYPE "altera_avalon_pio"


/*
 * row_19 configuration
 *
 */

#define ALT_MODULE_CLASS_row_19 altera_avalon_pio
#define ROW_19_BASE 0x2500130
#define ROW_19_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_19_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_19_CAPTURE 0
#define ROW_19_DATA_WIDTH 30
#define ROW_19_DO_TEST_BENCH_WIRING 0
#define ROW_19_DRIVEN_SIM_VALUE 0
#define ROW_19_EDGE_TYPE "NONE"
#define ROW_19_FREQ 50000000
#define ROW_19_HAS_IN 0
#define ROW_19_HAS_OUT 1
#define ROW_19_HAS_TRI 0
#define ROW_19_IRQ -1
#define ROW_19_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_19_IRQ_TYPE "NONE"
#define ROW_19_NAME "/dev/row_19"
#define ROW_19_RESET_VALUE 0
#define ROW_19_SPAN 16
#define ROW_19_TYPE "altera_avalon_pio"


/*
 * row_2 configuration
 *
 */

#define ALT_MODULE_CLASS_row_2 altera_avalon_pio
#define ROW_2_BASE 0x2500020
#define ROW_2_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_2_CAPTURE 0
#define ROW_2_DATA_WIDTH 30
#define ROW_2_DO_TEST_BENCH_WIRING 0
#define ROW_2_DRIVEN_SIM_VALUE 0
#define ROW_2_EDGE_TYPE "NONE"
#define ROW_2_FREQ 50000000
#define ROW_2_HAS_IN 0
#define ROW_2_HAS_OUT 1
#define ROW_2_HAS_TRI 0
#define ROW_2_IRQ -1
#define ROW_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_2_IRQ_TYPE "NONE"
#define ROW_2_NAME "/dev/row_2"
#define ROW_2_RESET_VALUE 0
#define ROW_2_SPAN 16
#define ROW_2_TYPE "altera_avalon_pio"


/*
 * row_20 configuration
 *
 */

#define ALT_MODULE_CLASS_row_20 altera_avalon_pio
#define ROW_20_BASE 0x2500140
#define ROW_20_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_20_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_20_CAPTURE 0
#define ROW_20_DATA_WIDTH 30
#define ROW_20_DO_TEST_BENCH_WIRING 0
#define ROW_20_DRIVEN_SIM_VALUE 0
#define ROW_20_EDGE_TYPE "NONE"
#define ROW_20_FREQ 50000000
#define ROW_20_HAS_IN 0
#define ROW_20_HAS_OUT 1
#define ROW_20_HAS_TRI 0
#define ROW_20_IRQ -1
#define ROW_20_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_20_IRQ_TYPE "NONE"
#define ROW_20_NAME "/dev/row_20"
#define ROW_20_RESET_VALUE 0
#define ROW_20_SPAN 16
#define ROW_20_TYPE "altera_avalon_pio"


/*
 * row_21 configuration
 *
 */

#define ALT_MODULE_CLASS_row_21 altera_avalon_pio
#define ROW_21_BASE 0x2500150
#define ROW_21_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_21_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_21_CAPTURE 0
#define ROW_21_DATA_WIDTH 30
#define ROW_21_DO_TEST_BENCH_WIRING 0
#define ROW_21_DRIVEN_SIM_VALUE 0
#define ROW_21_EDGE_TYPE "NONE"
#define ROW_21_FREQ 50000000
#define ROW_21_HAS_IN 0
#define ROW_21_HAS_OUT 1
#define ROW_21_HAS_TRI 0
#define ROW_21_IRQ -1
#define ROW_21_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_21_IRQ_TYPE "NONE"
#define ROW_21_NAME "/dev/row_21"
#define ROW_21_RESET_VALUE 0
#define ROW_21_SPAN 16
#define ROW_21_TYPE "altera_avalon_pio"


/*
 * row_22 configuration
 *
 */

#define ALT_MODULE_CLASS_row_22 altera_avalon_pio
#define ROW_22_BASE 0x2500160
#define ROW_22_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_22_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_22_CAPTURE 0
#define ROW_22_DATA_WIDTH 30
#define ROW_22_DO_TEST_BENCH_WIRING 0
#define ROW_22_DRIVEN_SIM_VALUE 0
#define ROW_22_EDGE_TYPE "NONE"
#define ROW_22_FREQ 50000000
#define ROW_22_HAS_IN 0
#define ROW_22_HAS_OUT 1
#define ROW_22_HAS_TRI 0
#define ROW_22_IRQ -1
#define ROW_22_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_22_IRQ_TYPE "NONE"
#define ROW_22_NAME "/dev/row_22"
#define ROW_22_RESET_VALUE 0
#define ROW_22_SPAN 16
#define ROW_22_TYPE "altera_avalon_pio"


/*
 * row_23 configuration
 *
 */

#define ALT_MODULE_CLASS_row_23 altera_avalon_pio
#define ROW_23_BASE 0x2500170
#define ROW_23_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_23_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_23_CAPTURE 0
#define ROW_23_DATA_WIDTH 30
#define ROW_23_DO_TEST_BENCH_WIRING 0
#define ROW_23_DRIVEN_SIM_VALUE 0
#define ROW_23_EDGE_TYPE "NONE"
#define ROW_23_FREQ 50000000
#define ROW_23_HAS_IN 0
#define ROW_23_HAS_OUT 1
#define ROW_23_HAS_TRI 0
#define ROW_23_IRQ -1
#define ROW_23_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_23_IRQ_TYPE "NONE"
#define ROW_23_NAME "/dev/row_23"
#define ROW_23_RESET_VALUE 0
#define ROW_23_SPAN 16
#define ROW_23_TYPE "altera_avalon_pio"


/*
 * row_3 configuration
 *
 */

#define ALT_MODULE_CLASS_row_3 altera_avalon_pio
#define ROW_3_BASE 0x2500030
#define ROW_3_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_3_CAPTURE 0
#define ROW_3_DATA_WIDTH 30
#define ROW_3_DO_TEST_BENCH_WIRING 0
#define ROW_3_DRIVEN_SIM_VALUE 0
#define ROW_3_EDGE_TYPE "NONE"
#define ROW_3_FREQ 50000000
#define ROW_3_HAS_IN 0
#define ROW_3_HAS_OUT 1
#define ROW_3_HAS_TRI 0
#define ROW_3_IRQ -1
#define ROW_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_3_IRQ_TYPE "NONE"
#define ROW_3_NAME "/dev/row_3"
#define ROW_3_RESET_VALUE 0
#define ROW_3_SPAN 16
#define ROW_3_TYPE "altera_avalon_pio"


/*
 * row_4 configuration
 *
 */

#define ALT_MODULE_CLASS_row_4 altera_avalon_pio
#define ROW_4_BASE 0x2500040
#define ROW_4_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_4_CAPTURE 0
#define ROW_4_DATA_WIDTH 30
#define ROW_4_DO_TEST_BENCH_WIRING 0
#define ROW_4_DRIVEN_SIM_VALUE 0
#define ROW_4_EDGE_TYPE "NONE"
#define ROW_4_FREQ 50000000
#define ROW_4_HAS_IN 0
#define ROW_4_HAS_OUT 1
#define ROW_4_HAS_TRI 0
#define ROW_4_IRQ -1
#define ROW_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_4_IRQ_TYPE "NONE"
#define ROW_4_NAME "/dev/row_4"
#define ROW_4_RESET_VALUE 0
#define ROW_4_SPAN 16
#define ROW_4_TYPE "altera_avalon_pio"


/*
 * row_5 configuration
 *
 */

#define ALT_MODULE_CLASS_row_5 altera_avalon_pio
#define ROW_5_BASE 0x2500050
#define ROW_5_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_5_CAPTURE 0
#define ROW_5_DATA_WIDTH 30
#define ROW_5_DO_TEST_BENCH_WIRING 0
#define ROW_5_DRIVEN_SIM_VALUE 0
#define ROW_5_EDGE_TYPE "NONE"
#define ROW_5_FREQ 50000000
#define ROW_5_HAS_IN 0
#define ROW_5_HAS_OUT 1
#define ROW_5_HAS_TRI 0
#define ROW_5_IRQ -1
#define ROW_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_5_IRQ_TYPE "NONE"
#define ROW_5_NAME "/dev/row_5"
#define ROW_5_RESET_VALUE 0
#define ROW_5_SPAN 16
#define ROW_5_TYPE "altera_avalon_pio"


/*
 * row_6 configuration
 *
 */

#define ALT_MODULE_CLASS_row_6 altera_avalon_pio
#define ROW_6_BASE 0x2500060
#define ROW_6_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_6_CAPTURE 0
#define ROW_6_DATA_WIDTH 30
#define ROW_6_DO_TEST_BENCH_WIRING 0
#define ROW_6_DRIVEN_SIM_VALUE 0
#define ROW_6_EDGE_TYPE "NONE"
#define ROW_6_FREQ 50000000
#define ROW_6_HAS_IN 0
#define ROW_6_HAS_OUT 1
#define ROW_6_HAS_TRI 0
#define ROW_6_IRQ -1
#define ROW_6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_6_IRQ_TYPE "NONE"
#define ROW_6_NAME "/dev/row_6"
#define ROW_6_RESET_VALUE 0
#define ROW_6_SPAN 16
#define ROW_6_TYPE "altera_avalon_pio"


/*
 * row_7 configuration
 *
 */

#define ALT_MODULE_CLASS_row_7 altera_avalon_pio
#define ROW_7_BASE 0x2500070
#define ROW_7_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_7_CAPTURE 0
#define ROW_7_DATA_WIDTH 30
#define ROW_7_DO_TEST_BENCH_WIRING 0
#define ROW_7_DRIVEN_SIM_VALUE 0
#define ROW_7_EDGE_TYPE "NONE"
#define ROW_7_FREQ 50000000
#define ROW_7_HAS_IN 0
#define ROW_7_HAS_OUT 1
#define ROW_7_HAS_TRI 0
#define ROW_7_IRQ -1
#define ROW_7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_7_IRQ_TYPE "NONE"
#define ROW_7_NAME "/dev/row_7"
#define ROW_7_RESET_VALUE 0
#define ROW_7_SPAN 16
#define ROW_7_TYPE "altera_avalon_pio"


/*
 * row_8 configuration
 *
 */

#define ALT_MODULE_CLASS_row_8 altera_avalon_pio
#define ROW_8_BASE 0x2500080
#define ROW_8_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_8_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_8_CAPTURE 0
#define ROW_8_DATA_WIDTH 30
#define ROW_8_DO_TEST_BENCH_WIRING 0
#define ROW_8_DRIVEN_SIM_VALUE 0
#define ROW_8_EDGE_TYPE "NONE"
#define ROW_8_FREQ 50000000
#define ROW_8_HAS_IN 0
#define ROW_8_HAS_OUT 1
#define ROW_8_HAS_TRI 0
#define ROW_8_IRQ -1
#define ROW_8_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_8_IRQ_TYPE "NONE"
#define ROW_8_NAME "/dev/row_8"
#define ROW_8_RESET_VALUE 0
#define ROW_8_SPAN 16
#define ROW_8_TYPE "altera_avalon_pio"


/*
 * row_9 configuration
 *
 */

#define ALT_MODULE_CLASS_row_9 altera_avalon_pio
#define ROW_9_BASE 0x2500090
#define ROW_9_BIT_CLEARING_EDGE_REGISTER 0
#define ROW_9_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ROW_9_CAPTURE 0
#define ROW_9_DATA_WIDTH 30
#define ROW_9_DO_TEST_BENCH_WIRING 0
#define ROW_9_DRIVEN_SIM_VALUE 0
#define ROW_9_EDGE_TYPE "NONE"
#define ROW_9_FREQ 50000000
#define ROW_9_HAS_IN 0
#define ROW_9_HAS_OUT 1
#define ROW_9_HAS_TRI 0
#define ROW_9_IRQ -1
#define ROW_9_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROW_9_IRQ_TYPE "NONE"
#define ROW_9_NAME "/dev/row_9"
#define ROW_9_RESET_VALUE 0
#define ROW_9_SPAN 16
#define ROW_9_TYPE "altera_avalon_pio"


/*
 * sram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sram_0 altera_up_avalon_sram
#define SRAM_0_BASE 0x0
#define SRAM_0_IRQ -1
#define SRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_0_NAME "/dev/sram_0"
#define SRAM_0_SPAN 2097152
#define SRAM_0_TYPE "altera_up_avalon_sram"

#endif /* __SYSTEM_H_ */
