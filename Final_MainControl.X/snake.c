#include "snake.h"

void snakeInit(){
	// setSnakeGameArray(BODY, 0, 0, 0);
	// setSnakeGameArray(BODY, 0, 1, 0);
	// setSnakeGameArray(HEAD, 0, 2, 0);

	//initialize array
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setSnakeGameArray(0, i, j, k);
			}
		}
	}
	snakeLength = 3;
	// pt b1 = {.lev = 0, .row = 0, .col = 0, .type = BODY};
	// pt b2 = {.lev = 0, .row = 1, .col = 0, .type = BODY};
	// pt head = {.lev = 0, .row = 2, .col = 0, .type = HEAD};
	// pushBackSnakeArray(head);
	// pushBackSnakeArray(b1);
	// pushBackSnakeArray(b2);
	refreshSnake();
}

void pushBackSnakeArray(pt body){
	snakeArray[snakeLength++] = body;
}



void snakeMove(uint8_t dir){
	if(!isBorder(getHeadLev(), getHeadRow(), getHeadCol(), dir)){
		switch(dir){
			case 2:
				break; 
		}
	}
	else{
		
	}
}

/**
 * Refresh snake pos in snakeGameArray
 */ 
void refreshSnake(){
	int i = 0;
	for(i = 0; i < snakeLength; i++){
		pt thisPoint = snakeArray[i];
		setSnakeGameArray(thisPoint.type, thisPoint.lev, thisPoint.row, thisPoint.col);
	}
}


/**
 * push status to LED
 */
void snakeSetLED(){
	// uint8_t buffer[64];
	int i = 0;
	int j = 0;
	int k = 0;
	uint8_t thisRow = 0;
	ledInit();

	setSnakeGameArray(HEAD, 0, 2, 0);



	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			thisRow = 0;
			for(k = COL_NUM; k > 0; k--){
				thisRow <<= 1;
				thisRow += !!(getSnakeGameArray(i, j, k - 1));			
			}
			setArray(thisRow, j, i);
		}
	}
}

void setSnakeGameArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	snakeGameArray[levIndex][rowIndex][colIndex] = type;
}

uint8_t getSnakeGameArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	return snakeGameArray[levIndex][rowIndex][colIndex];
}

uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	return 0;
}

uint8_t getHeadLev(){
	return 0;
}

uint8_t getHeadRow(){
	return 0;
}

uint8_t getHeadCol(){
	return 0;
}

void runSnakeTests(){
	lettersDisplayInit();
	snakeInit();
	snakeSetLED();
	testPrintLedStatus(); 
}
