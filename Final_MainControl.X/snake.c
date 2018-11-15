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
	snakeLength = 0;
	pt head = {.lev = 0, .row = 2, .col = 0, .type = HEAD};
	pt b1 = {.lev = 0, .row = 1, .col = 0, .type = BODY};
	pt b2 = {.lev = 0, .row = 0, .col = 0, .type = BODY};
	pushBackSnakeArray(head);
	pushBackSnakeArray(b1);
	pushBackSnakeArray(b2);
	refreshSnake();
}

void pushBackSnakeArray(pt body){
	snakeArray[snakeLength++] = body;
}



void snakeMove(uint8_t dir){
	if(!isBorder(getHeadLev(), getHeadRow();, getHeadCol(), dir) 
		&& !isBody(getHeadLev(), getHeadRow(), getHeadCol(), dir)){
		snakeMoveBody();
		snakeMoveHead(dir);
	}
	else{

	}
	refreshSnake();
}

void snakeMoveHead(uint8_t dir){
	switch(dir){
		//back
		case 2: 
			snakeArray[0].row -= 1;
			break; 
		//forward
		case 8:
			snakeArray[0].row += 1;
			break;
		//left
		case 4:
			snakeArray[0].col += 1;
			break;
		//right
		case 6:
			snakeArray[0].col -= 1;
			break;
		//down
		case 1:
			snakeArray[0].lev -= 1;
			break;
		//up
		case 7:
			snakeArray[0].lev += 1;
			break;
	}
}

void snakeMoveBody(){
	int i = 0;
	for(i = snakeLength; i > 1; i--){
		snakeArray[i - 1].lev = snakeArray[i - 2].lev;
		snakeArray[i - 1].row = snakeArray[i - 2].row;
		snakeArray[i - 1].col = snakeArray[i - 2].col;
	}
}

/**
 * Refresh snake pos in snakeGameArray
 */ 
void refreshSnake(){
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

	// setSnakeGameArray(HEAD, 0, 2, 0);



	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			thisRow = 0;
			for(k = COL_NUM; k > 0; k--){
				thisRow <<= 1;
				thisRow += !!(getSnakeGameArray(i, j, k - 1));			
			}
			setArray(thisRow, i, j);
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
	switch(dir){
		case 2: 
			if(rowIndex == 0) return 1; 
		case 8:
			if(rowIndex == ROW_NUM - 1) return 1;
		case 4:
			if(colIndex == COL_NUM - 1) return 1;
		case 6:
			if(colIndex == 0) return 1;
		case 1:
			if(levIndex == 0) return 1;
		case 7:
			if(levIndex == LEV_NUM - 1) return 1;
	}
	return 0;
}

uint8_t isBody(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	uint8_t targetLev = 0;
	uint8_t targetRow = 0;
	uint8_t targetCol = 0;
	switch(dir){
		case 2: 
			targetLev = levIndex;
			targetRow -= 1;
			targetCol = colIndex;
			break;
		case 8:
			targetLev = levIndex;
			targetRow += 1;
			targetCol = colIndex;
		case 4:
			
		case 6:
			
		case 1:
			
		case 7:
			
	}
	return 0;
}


uint8_t getHeadLev(){
	return snakeArray[0].lev;
}

uint8_t getHeadRow(){
	return snakeArray[0].row;
}

uint8_t getHeadCol(){
	return snakeArray[0].col;
}

void runSnakeTests(){
	lettersDisplayInit();
	snakeInit();
	snakeMove(8);
	snakeMove(4);
	snakeMove(7);
	snakeSetLED();
	testPrintLedStatus(); 
}
