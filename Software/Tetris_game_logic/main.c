#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "system.h"
#include "renderer.c"
#include "SRAM.c"
#include "blocks.h"
#include "colors.h"

#define pixels_x 640
#define pixels_y 480
#define block_height 26
#define block_width 26
#define delay 1000000

#define playingFieldStartX 190
#define playingFieldStartY 468

int playingField[18][10];
int movingBlockPosition[3][3][2];

//void timerISR(void* context) {
    // Increment the seconds counter
  //  seconds++;
//}

int main()
{
	int running = 1;
	int seconds = 0;

	//alt_u32 timerPeriod = ALT_CPU_FREQ / 1; // Set timer period for 1 second

	// Register the timer interrupt handler
	//alt_irq_register(TIMER_IRQ, NULL, timerISR);

	// Initialize and start the timer
	//IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE, 0x0);
	//IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_BASE, timerPeriod & 0xFFFF);
	//IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_BASE, (timerPeriod >> 16) & 0xFFFF);
	//IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE, 0x7);

	//int screen[480][640] = renderScreen();
	int movingBlock[3][3];
	int placingBlock = 0;
/*
	while(running == 1)
	{
		if(seconds == 1)
		{
			if(placingBlock == 0)
			{
				//movingBlock = randomBlock();
				placingBlock = 1;
				addBlockToField(movingBlock);
			}
			else
			{
				moveBlockDown(movingBlock);
			}

			newFrame();
			seconds = 0;
		}
		usleep(delay); // run again in 1 second
	}*/

	return running;
}

/*int addBlockToField(int block[3][3])
{
	for(int y = 0; y < 3; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			if(block[y][x] == 1)
			{
				playingField[0 + y][2 + x] = cyan;
				movingBlockPosition[y][x][0] = 0 + y;
				movingBlockPosition[y][x][1] = 2 + x;
			}
			else
			{
				playingField[0 + y][2 + x] = black;
			}
		}
	}
}

int moveBlockDown()
{
	int coords[2];
	for(int y = 0; y < 3; y++)
	{
		//for(int x = 0; x < 3; x++)
	//	{
			//coords = movingBlockPosition[y][x];
			//if(playingField[movingBlockPosition[0]][movingBlockPosition[1]] == black)
			//{

			//}
		}
	}
}

int rotate(int block[3][3])
{
	int newRotation = 0;

	for(int i = 0; i < sizeof(blocks) / sizeof(int); i++)
	{
		for(int n = 0; n < sizeof(blocks[i]) / sizeof(int); n++)
		{
			if(blocksEqual(block, blocks[i][n]) == 1)
			{
				if(n > 3)
				{
					newRotation = n + 1;
				}
				else
				{
					newRotation = 0;
				}

				return blocks[i][newRotation];
			}
		}
	}

}

int blocksEqual(block1, block2)
{
	for(int y = 0; y < 3; y++)
	{
		for(int x = 0; x < 3; x++)
		{
			//if(block1[y][x] != block2[y][x])
			//{
				//return 0;
			//}
		}
	}

	return 1;
}
int newFrame()
{

}

int randomBlock()
{
	return blocks[rand() % 7][rand() % 4];
}

int renderScreen()
{
	int beginScreen[480][640][3];
	int border_left = 183;
	int border_right = 455;

	for(int y = 0; y < 480; y++)
	{
		for(int x = 0; x < 640; x++)
		{
			if(x >= border_left && x <= border_left + 6 || x >= border_right && x <= border_right + 6 || y <= 5 || y >= 633)
			{
				//beginScreen[y][x] = grey;
			}
			else
			{
				//beginScreen[y][x] = black;
			}
		}
	}


}

int addPlayingFieldToScreen(int screen[480][640][3])
{
	for(int y = 0; y < 18; y++)
	{
		for(int x = 0; x < 10; x++)
		{
			for(int blockY; blockY < block_height; blockY++)
			{
				for(int blockX; blockX < block_width; blockX++)
				{
					//screen[(blockY * y) + playingFieldStartY][(blockX * x) + playingFieldStartX] = playingField[blockY][blockX];
				}
			}

		}
	}
}*/
