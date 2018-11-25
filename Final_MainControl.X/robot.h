#ifndef ROBOT_H
#define	ROBOT_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"
#include "utilities.h"

#define EMPTY  0
#define PLAYER 1
#define ENEMY  2
#define NUMBER_OF_ENEMIES 20
#define FLASH_MSEC 5000


uint8_t playerIsOn;
uint8_t robotGameArray[LEV_NUM][ROW_NUM][COL_NUM];
pt enemyArray[NUMBER_OF_ENEMIES];
pt player;

void runRobotGame();
void robotInit();
void generateEnemies();
void playerMove(uint8_t dir);
void enemiesMove();
void playerTeleport();
void setRobotGameArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t getRobotGameArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t isEnemy(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir);
void robotSetLED();

/*test methods*/
void runRobotTests();

#endif	/* ROBOT_H */

