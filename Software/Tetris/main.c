#include "sys/alt_stdio.h"
#include "system.h"
#include "io.h"
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include <stdlib.h>
#include <stdint.h>
#include "altera_avalon_pio_regs.h"
#include <altera_avalon_timer_regs.h>
#include <sys/alt_irq.h>
#include <stdio.h>

#define START_X 3
#define START_Y 0

int grid[24][10];
int rowAdresses[24] = {ROW_0_BASE, ROW_1_BASE, ROW_2_BASE, ROW_3_BASE, ROW_4_BASE, ROW_5_BASE, ROW_6_BASE, ROW_7_BASE, ROW_8_BASE, ROW_9_BASE, ROW_10_BASE, ROW_11_BASE, ROW_12_BASE, ROW_13_BASE, ROW_14_BASE, ROW_15_BASE, ROW_16_BASE, ROW_17_BASE, ROW_18_BASE, ROW_19_BASE, ROW_20_BASE, ROW_21_BASE, ROW_22_BASE, ROW_23_BASE};
int currentBlock[4][4][3];
int frameCounter = 0;
int gameSpeed = 48;
typedef enum {I, J, L, O, S, T, Z} blocks;
typedef enum {MOVE_LEFT, MOVE_RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOKWISE} movements;
blocks currentBlockType;
int gameOver = 0;
int score = 0;
int linesClearedThisLevel = 0;
int linesCleared = 0;
int level = 0;
int levelIncreaseRequirements[29] = { 10, 20, 30, 40, 50, 60, 70,80, 90, 100, 100, 100, 100, 100, 100, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 200, 200, 200};
int levelSpeeds[29] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};

void moveLeftInterrupt(void* context)
{
	// Reset interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(MOVE_LEFT_BASE,0);
	if(gameOver == 0)
	{
		move(MOVE_LEFT);
		drawGrid();
	}
	else
	{
		resetGame();
	}
}

void moveRightInterrupt(void* context)
{
	// Reset interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(MOVE_RIGHT_BASE,0);
	if(gameOver == 0)
	{
		move(MOVE_RIGHT);
		drawGrid();
	}
}

void rotateLeftInterrupt(void* context)
{
	// Reset interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(ROTATE_LEFT_BASE,0);
	if(gameOver == 0)
	{
		rotate(ROTATE_COUNTERCLOKWISE);
		drawGrid();
	}
}

void rotateRightInterrupt(void* context)
{
	// Reset interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(ROTATE_RIGHT_BASE,0);
	if(gameOver == 0)
	{
		rotate(ROTATE_CLOCKWISE);
		drawGrid();
	}
}

void frameTimerInterrupt(void *context, alt_u32 id)
{
	// Reset interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(FRAME_TIMER_BASE, 0);

	if(IORD_ALTERA_AVALON_PIO_DATA(RESET_GAME_BASE) == 1)
	{
		resetGame();
	}

	if(gameOver == 0)
	{
		int newSpeed = 0;
		if(IORD_ALTERA_AVALON_PIO_DATA(FAST_MOVE_BASE) == 1)
		{
			newSpeed = 3;

		}
		else
		{
			newSpeed = levelSpeeds[level];
		}

		if(newSpeed != gameSpeed)
		{
			frameCounter = 0;
			gameSpeed = newSpeed;
		}

		frameCounter = frameCounter + 1;
		if(frameCounter == gameSpeed)
		{
			gravity();
			drawGrid();
			frameCounter = 0;
		}
	}
}

int main()
{
  unsigned char rowArray[30];
  char binString = "010000000000000000000000000000";

  clearGrid();

  blocks randomBlock = (rand() % 7);
  createBlock(randomBlock);

  initInterupts();
  writeScore(score);
  writeLevel(level);

  return 0;
}

void initInterupts()
{
	// move left interrupt
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(MOVE_LEFT_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(MOVE_LEFT_BASE,0);
	alt_ic_isr_register(MOVE_LEFT_IRQ_INTERRUPT_CONTROLLER_ID, MOVE_LEFT_IRQ, moveLeftInterrupt, NULL, 0x0);

	// move right interrupt
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(MOVE_RIGHT_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(MOVE_RIGHT_BASE,0);
	alt_ic_isr_register(MOVE_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID, MOVE_RIGHT_IRQ, moveRightInterrupt, NULL, 0x0);

	// rotate left interrupt
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(ROTATE_LEFT_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(ROTATE_LEFT_BASE,0);
	alt_ic_isr_register(ROTATE_LEFT_IRQ_INTERRUPT_CONTROLLER_ID, ROTATE_LEFT_IRQ, rotateLeftInterrupt, NULL, 0x0);

	// rotate right interrupt
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(ROTATE_RIGHT_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(ROTATE_RIGHT_BASE,0);
	alt_ic_isr_register(ROTATE_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID, ROTATE_RIGHT_IRQ, rotateRightInterrupt, NULL, 0x0);

	// frame timer
	alt_ic_isr_register(FRAME_TIMER_IRQ_INTERRUPT_CONTROLLER_ID, FRAME_TIMER_IRQ, (void *) frameTimerInterrupt, NULL, 0x0);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(FRAME_TIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
													| ALTERA_AVALON_TIMER_CONTROL_START_MSK
													| ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}

void resetGame()
{
	clearGrid();
	blocks randomBlock = (rand() % 7);
	createBlock(randomBlock);
	gameOver = 0;
	score = 0;
	level = 0;
	linesClearedThisLevel = 0;
	linesCleared = 0;
	writeScore(score);
	writeLevel(level);
}

void writeLevel(int level)
{
	int hexDisplays[6] = {0};
	hexDisplays[0] = HEX_6_BASE;
	hexDisplays[1] = HEX_7_BASE;

	writeHex(level, hexDisplays);
}

void writeScore(int score)
{
	int hexDisplays[6] = { HEX_0_BASE, HEX_1_BASE, HEX_2_BASE, HEX_3_BASE, HEX_4_BASE, HEX_5_BASE};
	writeHex(score, hexDisplays);

	//IOWR_ALTERA_AVALON_PIO_DATA(hexDisplays[0], digitToHex(0));
}

void writeHex(int number, int hexDisplays[6])
{
	int digitsWriten = 0;

	while(number != 0 && hexDisplays[6]){
	        int digit = number % 10;
	        number = number / 10;
	        IOWR_ALTERA_AVALON_PIO_DATA(hexDisplays[digitsWriten], digitToHex(digit));
	        digitsWriten = digitsWriten + 1;
	    }

	for(int i = digitsWriten; i < 6; i++)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(hexDisplays[i], digitToHex(0));
	}
}

int digitToHex(int digit)
{
	uint8_t convertedDigit = 0;
	switch(digit)
	{
		case 0:
			convertedDigit = 0b1000000;
			break;
		case 1:
			convertedDigit = 0b1111001;
			break;
		case 2:
			convertedDigit = 0b0100100;
			break;
		case 3:
			convertedDigit = 0b0110000;
			break;
		case 4:
			convertedDigit = 0b0011001;
			break;
		case 5:
			convertedDigit = 0b0010010;
			break;
		case 6:
			convertedDigit = 0b0000010;
			break;
		case 7:
			convertedDigit = 0b1111000;
			break;
		case 8:
			convertedDigit = 0b0000000;
			break;
		case 9:
			convertedDigit = 0b0000100;
			break;
	}

	return convertedDigit;
}

void removeCompletedLines()
{
	int completedLines = 0;
	int lineCompleted = 1;
	int start_y = 24;

	for(int y = 23; y >= 0; y--)
	{
		for(int x = 0; x < 10; x++)
		{
			if(grid[y][x] == 0)
			{
				if(completedLines > 0)
				{
					for(int j = 0; j < completedLines; j++)
					{
						for(int x = 0; x < 10; x++)
						{
							grid[start_y - j][x] = 0;
						}
					}

					for(int j = (start_y - completedLines); j >= 0; j--)
					{
						for(int x = 0; x < 10; x++)
						{
							grid[j + completedLines][x] = grid[j][x];
						}
					}

					drawGrid();

					addScore(completedLines);
					removeCompletedLines();
				}

				lineCompleted = 0;
				start_y = 24;
				completedLines = 0;
			}
		}

		if(lineCompleted == 1)
		{
			if(start_y == 24)
			{
				start_y = y;
				completedLines = 1;
			}
			else
			{
				completedLines = completedLines + 1;
			}
		}

		lineCompleted = 1;
	}
}

void addScore(int completedLines)
{
	switch(completedLines)
	{
		case 1:
			score = score + 40;
			break;
		case 2:
			score = score + 100;
			break;
		case 3:
			score = score + 300;
			break;
		case 4:
			score = score + 1200;
			break;
	}

	writeScore(score);
	linesCleared = linesCleared + completedLines;
	linesClearedThisLevel = linesClearedThisLevel + completedLines;
	updateLevel();
}

void updateLevel()
{
	if(linesClearedThisLevel >=  levelIncreaseRequirements[level])
	{
		linesClearedThisLevel = linesClearedThisLevel - levelIncreaseRequirements[level];
		level = level + 1;
		frameCounter = 0;
		gameSpeed = levelSpeeds[level];
		writeLevel(level);
	}
}

int canMoveDown(int newLocation[4][4][3])
{

	// Check if the block has reached the bottom;
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(newLocation[y][x][2] != 0)
			{
				if(newLocation[y][x][0] > 23)
				{
					return 0;
				}
			}
		}
	}

	// Get the bottom coords
	int bottomCoords[4][3];
	memset(bottomCoords, 0, sizeof(bottomCoords));
	int currentBottomCoord[3];
	memset(currentBottomCoord, 0, sizeof(currentBottomCoord));
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			if(newLocation[y][x][2] != 0)
			{
				currentBottomCoord[0] = newLocation[y][x][0];
				currentBottomCoord[1] = newLocation[y][x][1];
				currentBottomCoord[2] = newLocation[y][x][2];
			}
		}

		bottomCoords[x][0] = currentBottomCoord[0];
		bottomCoords[x][1] = currentBottomCoord[1];
		bottomCoords[x][2] = currentBottomCoord[2];
	}

	for(int i = 0; i < 4; i++)
	{
		if(grid[bottomCoords[i][0]][bottomCoords[i][1]] != 0)
		{
			return 0;
		}
	}

	return 1;
}

int canMoveToSide(int newLocation[4][4][3], movements movement)
{
	int sideCoords[4][3];
	memset(sideCoords, 0, sizeof(sideCoords));
	int currentsideCoord[3];
	memset(currentsideCoord, 0, sizeof(currentsideCoord));

	for(int y = 0; y < 4; y++)
	{
		if(movement == MOVE_LEFT || movement == ROTATE_CLOCKWISE)
		{
			for(int x = 3; x >= 0; x--)
			{
				if(newLocation[y][x][2] != 0)
				{
					if(newLocation[y][x][1] < 0 || newLocation[y][x][1] > 9)
					{
						return 0;
					}

					currentsideCoord[0] = newLocation[y][x][0];
					currentsideCoord[1] = newLocation[y][x][1];
					currentsideCoord[2] = newLocation[y][x][2];
				}

			}
		}
		else
		{
			for(int x = 0; x < 4; x++)
			{
				if(newLocation[y][x][2] != 0)
				{
					if(newLocation[y][x][1] < 0 || newLocation[y][x][1] > 9)
					{
						return 0;
					}

					currentsideCoord[0] = newLocation[y][x][0];
					currentsideCoord[1] = newLocation[y][x][1];
					currentsideCoord[2] = newLocation[y][x][2];
				}

			}
		}

		sideCoords[y][0] = currentsideCoord[0];
		sideCoords[y][1] = currentsideCoord[1];
		sideCoords[y][2] = currentsideCoord[2];
	}

	for(int i = 0; i < 4; i++)
	{
		if(sideCoords[i][2] != 0)
		{
			if(grid[sideCoords[i][0]][sideCoords[i][1]] != 0)
			{
				return 0;
			}
		}

	}

	return 1;
}

int canRotate(int newLocation[4][4][3], movements movement)
{

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(newLocation[y][x][2] != 0)
			{
				if(newLocation[y][x][1] < 0 || newLocation[y][x][1] > 9)
				{
					return 0;
				}

				for(int cur_y = 0; cur_y < 4; cur_y++)
				{
					for(int cur_x = 0; cur_x < 4; cur_x++)
					{
						//if(currentLocation[cur_y][cur[]])
					}
				}
			}
		}
	}

/*	if(canMoveToSide(newLocation, movement) == 0 && canMoveDown(newLocation) == 0)
	{
		return 0;
	}*/

	return 1;
}

void gravity()
{
	int newLocation[4][4][3];
	memcpy(newLocation, currentBlock, sizeof(newLocation));

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			newLocation[y][x][0] = newLocation[y][x][0] + 1;
		}
	}

	if(canMoveDown(newLocation) == 1)
	{
		removeBlockFromGrid(currentBlock);
		memcpy(currentBlock, newLocation, sizeof(currentBlock));
		addBlockToGrid(currentBlock);
	}
	else
	{
		removeCompletedLines();
		blocks randomBlock = (rand() % 7);
		createBlock(randomBlock);
	}

}

void move(movements movement)
{
	int newLocation[4][4][3];
	memcpy(newLocation, currentBlock, sizeof(newLocation));

	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(movement == MOVE_LEFT)
			{
				newLocation[y][x][1] = newLocation[y][x][1] - 1;
			}
			else if(movement == MOVE_RIGHT)
			{
				newLocation[y][x][1] = newLocation[y][x][1] + 1;
			}
		}
	}

	if(canMoveToSide(newLocation, movement) == 1)
	{
		removeBlockFromGrid(currentBlock);
		memcpy(currentBlock, newLocation, sizeof(currentBlock));
		addBlockToGrid(currentBlock);
	}

}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void rotate(movements movement)
{
	int block_max_x;
	int block_max_y;
	switch(currentBlockType)
	{
		case I:
		case L:
		case J:
			block_max_x = 4;
			block_max_y = 4;
			break;
		case S:
		case Z:
		case T:
			block_max_x = 3;
			block_max_y = 3;
			break;
		default:
			return;
	}



	int newLocation[4][4][3];
	//memcpy(newLocation, currentBlock, sizeof(newLocation));

	memset(newLocation, 0, sizeof(newLocation));

	int original_x;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if(movement == ROTATE_CLOCKWISE)
			{
				newLocation[x][3 - y][0] = currentBlock[y][x][0] - (y - x);
				newLocation[x][3 - y][1] = currentBlock[y][x][1] - (x - (3 - y));
				newLocation[x][3 - y][2] = currentBlock[y][x][2];
			}
			else if(movement == ROTATE_COUNTERCLOKWISE)
			{
				newLocation[3 - x][y][0] = currentBlock[y][x][0] - (y - (3 - x));
				newLocation[3 - x][y][1] = currentBlock[y][x][1] - (x - y);
				newLocation[3 - x][y][2] = currentBlock[y][x][2];
			}

		}
	}

	if(canRotate(newLocation, movement) == 1)
	{
		removeBlockFromGrid(currentBlock);
		memcpy(currentBlock, newLocation, sizeof(currentBlock));
		addBlockToGrid(currentBlock);
	}
}

int createBlock(blocks blockType)
{
	int newBlock[4][4][3];
	int start_x = START_X;
	  	int start_y = START_Y;
	  	for(int y = 0; y < 4; y++)
	  	{
	  	  for(int x = 0; x < 4; x++)
	  	  {
	  		newBlock[y][x][0] = start_y;
	  		newBlock[y][x][1] = start_x;
	  		newBlock[y][x][2] = 0;
			start_x = start_x + 1;
	  	  }
	  	  start_y = start_y + 1;
	  	  start_x = START_X;
	  	}

	switch(blockType)
	{
		case I:
			newBlock[0][0][2] = 6;
			newBlock[1][0][2] = 6;
			newBlock[2][0][2] = 6;
			newBlock[3][0][2] = 6;
			break;
		case J:
			newBlock[0][1][2] = 5;
			newBlock[1][1][2] = 5;
			newBlock[2][1][2] = 5;
			newBlock[2][0][2] = 5;
			break;
		case L:
			newBlock[0][0][2] = 7;
			newBlock[1][0][2] = 7;
			newBlock[2][0][2] = 7;
			newBlock[2][1][2] = 7;
			break;
		case O:
			newBlock[0][0][2] = 1;
			newBlock[0][1][2] = 1;
			newBlock[1][0][2] = 1;
			newBlock[1][1][2] = 1;
			break;
		case S:
			newBlock[0][1][2] = 4;
			newBlock[0][2][2] = 4;
			newBlock[1][0][2] = 4;
			newBlock[1][1][2] = 4;
			break;
		case T:
			newBlock[0][0][2] = 2;
			newBlock[0][1][2] = 2;
			newBlock[0][2][2] = 2;
			newBlock[1][1][2] = 2;
			break;
		case Z:
			newBlock[0][0][2] = 3;
			newBlock[0][1][2] = 3;
			newBlock[1][1][2] = 3;
			newBlock[1][2][2] = 3;
			break;
	}

	if(isGameOver(newBlock) == 0)
	{
		memcpy(currentBlock, newBlock, sizeof(currentBlock));
		currentBlockType = blockType;
	}
}

int isGameOver(int newBlock[4][4][3])
{
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  if(newBlock[y][x][2] != 0)
		  {
			  if(grid[newBlock[y][x][0]][newBlock[y][x][1]] != 0)
			  {
				  gameOver = 1;
				  return 1;
			  }
		  }
	  }
	}
	return 0;
}

void addBlockToGrid(int block[4][4][3])
{
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  if(block[y][x][2] != 0)
		  {
			  grid[block[y][x][0]][block[y][x][1]] = block[y][x][2];
		  }
	  }
	}
}

void removeBlockFromGrid(int block[4][4][3])
{
	for(int y = 0; y < 4; y++)
	{
	  for(int x = 0; x < 4; x++)
	  {
		  if(block[y][x][2] != 0)
		  {
			  if(grid[block[y][x][0]][block[y][x][1]] != 0)
			  {
				  grid[block[y][x][0]][block[y][x][1]] = 0;
			  }
		  }
	  }
	}
}

int clearGrid()
{
	for(int y = 0; y < 24; y++)
	{
	  for(int x = 0; x < 10; x++)
	  {
		  grid[y][x] = 0;
		  IOWR_ALTERA_AVALON_PIO_DATA(rowAdresses[y], 0b00000000000000000000000000000000);
	  }
	}
}

int drawGrid()
{
	uint32_t row = 0b00000000000000000000000000000000;
    int cursor = 29;
	 for(int y = 0; y <= 23; y++)
		  {
			  cursor = 29;
			  for(int x = 0; x <= 9; x++)
			  {
				  if(grid[y][x] != 0)
				  {
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

void visualizeBlock(int block[4][4][3])
{
	char line[4];
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(block[y][x][2] == 0)
			{
				line[x] = '-';
			}
			else
			{
				line[x] = '*';
			}
		}

		printf("%s\n", line);
	}
}


