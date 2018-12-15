#include "snake.h"

void runSnakeGame(){
	ledInit();
	snakeInit();
	generateFood();
	snakeSetLED();
	newRefresh();
	uint8_t dir = 0;
	// test();
	while(1){
		uint8_t input = decodeFromInputControl();
        if(input == 1)
            break;
		dir = checkDir();
		if(dir == FORWARD) dir = 8;
		else if(dir == BACKWARD) dir = 2;
		else if(dir == LEFT) dir = 4;
		else if(dir == RIGHT) dir = 6;
		else if(dir == UP) dir = 7;
		else if(dir == DOWN) dir = 1;
		else dir = 0;
		if(dir > 0 && dir < 9 && dir != 3 && dir != 5){
			snakeMove(dir);
			snakeSetLED();
			changed = 1;
			dir = 0;
		}
		newRefresh();	
	}
	
	// while(1){
	// 	uint8_t dir  = 0;
	// 	// uint8_t input = decodeFromInputControl();
 //  //       if(input == 7)
 //  //           break;
 //  //       else{
 //  //       	if(input == 1) dir = 8;
 //  //       	else if(input == 2) dir = 2;
 //  //       	else if(input == 3) dir = 4;
 //  //       	else if(input == 4) dir = 6;
 //  //       	else if(input == 5) dir = 7;
 //  //       	else if(input == 6) dir = 1;
 //  //       }
	// 	dir = checkDir();
	// 	if(dir > 0 && dir < 9 && dir != 3 && dir != 5){
	// 		snakeMove(dir);
	// 		snakeSetLED();
	// 		newRefresh();
	// 	} 
	// }
}

void snakeInit(){
	isMsg = 0;
	isSnake = 1;
	//initialize timer for random number
	ANSELB = 0;
	TRISB = TRISB | 0x2F80;
	T1CON = 0x8010;
	TMR1 = 0;
	//initialize array
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setSnakeGameArray(EMPTY, i, j, k);
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
	changed = 1;
	// generateFood();
}

void generateFood(){
	int i = 0;
	int isEmpty = 0;
	uint8_t foodLev = 0;
	uint8_t foodRow = 0;
	uint8_t foodCol = 0;
	
	//check if this pos is occupied by the snake
	while(!isEmpty){
		foodLev = TMR1 % LEV_NUM;
		foodRow = (TMR1 >> 1) % ROW_NUM;
		foodCol = (TMR1 >> 2) % COL_NUM;
		isEmpty = 1;
		// for(i = 0; i < snakeLength; i++){
		// 	if(snakeArray[i].lev == foodLev && snakeArray[i].row == foodRow && snakeArray[i].col == foodCol){
		// 		isEmpty = 0;
		// 	}
		// }
		if(getSnakeGameArray(foodLev, foodRow, foodCol) == HEAD || getSnakeGameArray(foodLev, foodRow, foodCol) == BODY)
			isEmpty = 0;
	}
	setSnakeGameArray(FOOD, foodLev, foodRow, foodCol);	
}



void snakeMove(uint8_t dir){
	uint8_t lastLev = 0;
	uint8_t lastRow = 0;
	uint8_t lastCol = 0;
	if(isBorder(getHeadLev(), getHeadRow(), getHeadCol(), dir) 
		|| isBody(getHeadLev(), getHeadRow(), getHeadCol(), dir)){

	}
	else if(isFood(getHeadLev(), getHeadRow(), getHeadCol(), dir)){
		lastLev = snakeArray[snakeLength].lev;
		lastRow = snakeArray[snakeLength].row;
		lastCol = snakeArray[snakeLength].col;
		snakeMoveBody();
		eat(getHeadLev(), getHeadRow(), getHeadCol(), dir, lastLev, lastRow, lastCol);
		snakeMoveHead(dir);
		refreshSnake();
		generateFood();
	}
	else{
		snakeMoveBody();
		snakeMoveHead(dir);
		refreshSnake();
	}
	
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

void eat(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir, uint8_t lastLev, uint8_t lastRow, uint8_t lastCol){
	uint8_t targetLev = levIndex;
	uint8_t targetRow = rowIndex;
	uint8_t targetCol = colIndex;
	switch(dir){
		case 2: 
			targetRow -= 1;
			break;
		case 8:
			targetRow += 1;
			break;
		case 4:
			targetCol += 1;
			break;
		case 6:
			targetCol -= 1;
			break;
		case 1:
			targetLev -= 1;
			break;
		case 7:
			targetLev += 1;
			break;
	}
	setSnakeGameArray(0, targetLev, targetRow, targetCol);
	pt new = {.lev = lastLev, .row = lastRow, .col = lastCol, .type = BODY};
	pushBackSnakeArray(new);
}

// uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
// 	switch(dir){
// 		case 2: 
// 			if(rowIndex == 0) return 1; 
// 			else return 0;
// 		case 8:
// 			if(rowIndex == ROW_NUM - 1) return 1;
// 			else return 0;
// 		case 4:
// 			if(colIndex == COL_NUM - 1) return 1;
// 			else return 0;
// 		case 6:
// 			if(colIndex == 0) return 1;
// 			else return 0;
// 		case 1:
// 			if(levIndex == 0) return 1;
// 			else return 0;
// 		case 7:
// 			if(levIndex == LEV_NUM - 1) return 1;
// 			else return 0;
// 	}
// 	return 0;
// }

uint8_t isBody(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	uint8_t targetLev = levIndex;
	uint8_t targetRow = rowIndex;
	uint8_t targetCol = colIndex;
	switch(dir){
		case 2: 
			targetRow -= 1;
			break;
		case 8:
			targetRow += 1;
			break;
		case 4:
			targetCol += 1;
			break;
		case 6:
			targetCol -= 1;
			break;
		case 1:
			targetLev -= 1;
			break;
		case 7:
			targetLev += 1;
			break;
	}
	// for(i = 1; i < snakeLength; i++){
	// 	if(snakeArray[i].lev == targetLev && snakeArray[i].row == targetRow && snakeArray[i].col == targetCol){
	// 		return 1;
	// 	}
	// }
	if(getSnakeGameArray(targetLev, targetRow, targetCol) == BODY) return 1;
	return 0;
}

uint8_t isFood(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	uint8_t targetLev = levIndex;
	uint8_t targetRow = rowIndex;
	uint8_t targetCol = colIndex;
	switch(dir){
		case 2: 
			targetRow -= 1;
			break;
		case 8:
			targetRow += 1;
			break;
		case 4:
			targetCol += 1;
			break;
		case 6:
			targetCol -= 1;
			break;
		case 1:
			targetLev -= 1;
			break;
		case 7:
			targetLev += 1;
			break;
	}
	if(getSnakeGameArray(targetLev, targetRow, targetCol) == FOOD) return 1;
	return 0;
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
				if(getSnakeGameArray(i, j, k) == HEAD || getSnakeGameArray(i, j, k) == BODY)
					setSnakeGameArray(EMPTY, i, j, k);
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
	resetLed(); //clear cuboidArray first
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

uint8_t getHeadLev(){
	return snakeArray[0].lev;
}

uint8_t getHeadRow(){
	return snakeArray[0].row;
}

uint8_t getHeadCol(){
	return snakeArray[0].col;
}

void pushBackSnakeArray(pt body){
	snakeArray[snakeLength++] = body;
}

void runSnakeTests(){
	uart_init();
	// snakeInit();
	// snakeMove(8);
	// snakeMove(4);
	// snakeMove(7);
	// snakeSetLED();
	// testPrintLedStatus();
	snakeInit();
	snakeSetLED();
	testPrintLedStatus();
	while(1){
		char input = uart_read();
		uint8_t dir = input - 48;
		if(dir > 0 && dir < 9 && dir != 3 && dir != 5){
			snakeMove(dir);
			snakeSetLED();
			testPrintLedStatus();
		} 
	} 
}
