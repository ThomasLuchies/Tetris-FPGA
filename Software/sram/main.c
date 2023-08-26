/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "sys/alt_stdio.h"
#include "system.h"
#include "io.h"
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include <stdlib.h>
#include <stdint.h>

#define START_X 3
#define START_Y 0

int grid[24][10];
int rowAdresses[24] = {ROW_0_BASE, ROW_1_BASE, ROW_2_BASE, ROW_3_BASE, ROW_4_BASE, ROW_5_BASE, ROW_6_BASE, ROW_7_BASE, ROW_8_BASE, ROW_9_BASE, ROW_10_BASE, ROW_11_BASE, ROW_12_BASE, ROW_13_BASE, ROW_14_BASE, ROW_15_BASE, ROW_16_BASE, ROW_17_BASE, ROW_18_BASE, ROW_19_BASE, ROW_20_BASE, ROW_21_BASE, ROW_22_BASE, ROW_23_BASE};
int currentBlock[4][4][3];
typedef enum {I, J, L, O, S, T, Z} blocks;
int main()
{

  unsigned char rowArray[30];
  char binString = "010000000000000000000000000000";

  clearGrid();
  	int start_x = START_X;
  	int start_y = START_Y;
  	for(int y = 0; y < 4; y++)
  	{
  	  for(int x = 0; x < 4; x++)
  	  {
		currentBlock[y][x][0] = start_y;
		currentBlock[y][x][1] = start_x;
		if(x == 0)
		{
			currentBlock[y][x][2] = 6;
		}
		else
		{
			currentBlock[y][x][2] = 0;
		}

		start_x = start_x + 1;
  	  }
  	  start_y = start_y + 1;
  	  start_x = START_X;
  	}

  /* Event loop never exits. */
  addBlockToGrid(currentBlock);
  while (1)
  {
	  gravity();
	  drawGrid();


	  //IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE));
	  //IOWR_ALTERA_AVALON_PIO_DATA(rowAdresses[0], row);
	  //IOWR_ALTERA_AVALON_PIO_DATA(rowAdresses[1], 0b010010000000000000000000000000);
	  //IOWR_ALTERA_AVALON_PIO_DATA(ROW_2_BASE, 0b00010000000000000000000000000000);
	    usleep(1000000);
  }

  return 0;
}

void gravity()
{
	removeBlockFromGrid(currentBlock);
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			currentBlock[y][x][0] = currentBlock[y][x][0] + 1;
		}
	}
	addBlockToGrid(currentBlock);
}

/*int createBlock(blocks blockType, int out_block[4][4][3])
{
	int block[4][4][3];
	int start_x;
	int start_y;
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  block[y][x][0] = start_y;
		  block[y][x][] = start_x;
		  block[y][x][0] = 0;
		  start_x = start_x + 1;
	  }
	  start_y = start_y + 1;
	}

	switch(blockType)
	{
		case I:
			break;
		case J:
			break;
		case L:
			break;
		case O:
			break;
		case S:
			break;
		case T:
			break;
		case Z:
			break;
	}

	return block;
}*/

void addBlockToGrid(int block[4][4][3])
{
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  grid[block[y][x][0]][block[y][x][1]] = block[y][x][2];
	  }
	}
}

void removeBlockFromGrid(int block[4][4][3])
{
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  if(grid[block[y][x][0]][block[y][x][1]] != 0)
		  {
			  grid[block[y][x][0]][block[y][x][1]] = 0;
		  }
	  }
	}
}

int clearGrid()
{
	for(int y = 0; y < 23; y++)
	{
	  for(int x = 0; x < 9; x++)
	  {
		  grid[y][x] = 0;
	  }
	}
}

int drawGrid()
{
	uint32_t row = 0b00000000000000000000000000000000;
    int cursor = 29;
	 for(int y = 0; y < 23; y++)
		  {
			  cursor = 29;
			  for(int x = 0; x <= 9; x++)
			  {
				  if(grid[y][x] != 0)
				  {
					  printf("x: %d, y: %d, value: %d", x, y, grid[y][x]);
					  switch(grid[y][x])
					  {
					  	  case 1:
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
					  		  break;
					  	  case 2:
					  		  row |= (0 << cursor);
					  		  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  break;
					  	 case 3:
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  break;
					  	 case 4:
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  break;
					  	 case 5:
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  break;
					  	 case 6:
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (0 << cursor);
							  cursor = cursor - 1;
							  break;
					  	 case 7:
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  row |= (1 << cursor);
							  cursor = cursor - 1;
							  break;
					  }
				  }
				  else
				  {
					  cursor = cursor - 3;
				  }
			  }
			  IOWR_ALTERA_AVALON_PIO_DATA(rowAdresses[y], row);
			  row = 0b00000000000000000000000000000000;
		  }
}

void printBinary(int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
}
