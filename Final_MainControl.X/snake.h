#ifndef SNAKE_H
#define	SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"

#define HEAD 1
#define BODY 2
#define FOOD 3
#define MAX_LENGTH 20

typedef struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	uint8_t type;
} pt;

uint8_t snakeLength;
//Array that stores all the point info
//Reflects what's shown on LEDs
//0 => empty, 1 => snake head, 2 => body, 3 => food
uint8_t snakeGameArray[LEV_NUM][ROW_NUM][COL_NUM]; 
//stores only the snake
//index 0 is head
pt snakeArray[MAX_LENGTH];
pt fruit;

void snakeInit();
void generateFood();
void snakeMove(uint8_t dir); //2=>back 8=>forward 4=>left 6=>right 1=>down 7=>up   
void snakeMoveHead(uint8_t dir);
void snakeMoveBody();
void eat();
void refreshSnake();
uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir);
uint8_t isBody(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir);
void setSnakeGameArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t getSnakeGameArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
void pushBackSnakeArray(pt body);
uint8_t getHeadLev();
uint8_t getHeadRow();
uint8_t getHeadCol();
uint8_t random();
void snakeSetLED();

/*test methods*/
void runSnakeTests();

#endif	/* SNAKE_H */

