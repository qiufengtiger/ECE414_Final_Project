#ifndef ROBOT_H
#define	ROBOT_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"

#define PLAYER 1
#define ENEMY  2
#define NUMBER_OF_ENEMIES 20

typedef struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	//uint8_t type;
} pt;

uint8_t robotGameArray[LEV_NUM][ROW_NUM][COL_NUM];
pt enemyArray[NUMBER_OF_ENEMIES];

void runRobotGame();
void robotInit();
void generateEnemies();
void playerMove();
void enemyMove();
void playerTeleport();
void setRobotGameArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t getRobotGameArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t random();

#endif	/* ROBOT_H */

