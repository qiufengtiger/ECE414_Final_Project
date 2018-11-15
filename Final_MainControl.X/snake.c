#include "snake.h"

void snakeInit(){
	setSnakeArray(BODY, 0, 0, 0);
	setSnakeArray(BODY, 0, 1, 0);
	setSnakeArray(BODY, 0, 2, 0);
}

void setSnakeArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	snakeArray[levIndex][rowIndex][colIndex] = type;
}

void move(uint8_t dir){
	if(!isBorder(getHeadLev(), getHeadRow(), getHeadCol(), dir)){
		switch(dir){
			case 2:
				break; 
		}
	}
	else{
		
	}
}

