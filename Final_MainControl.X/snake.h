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

struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	uint8_t type;
} pt;

void snakeInit();
void generateFood();
void move(uint8_t dir); //2=>back 8=>forward 4=>left 6=>right 1=>down 7=>up   
void eat();
void refresh();
uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir);
uint8_t isBody(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir);
void setSnakeArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t getHeadLev();
uint8_t getHeadRow();
uint8_t getHeadCol();
uint8_t random();

uint8_t snakeLength;
uint8_t snakeArray[LEV_NUM][ROW_NUM][COL_NUM]; //0 => empty, 1 => snake head, 2 => body, 3 => food


#endif	/* SNAKE_H */

