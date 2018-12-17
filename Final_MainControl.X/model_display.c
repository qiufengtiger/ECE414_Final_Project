#include "model_display.h"

void runModelDisplay(){
	ledInit();
	modelDisplayInit();
	readModelFile();
	// setModelArray(1, 15, 1, 1);
	modelSetLED();
	uint8_t dir = 0;
	while(1){
		uint8_t input = decodeFromInputControl();
        if(input == 1)
            break;
		dir = checkDir();
		if(dir == LEFT || dir == RIGHT){
			rotate(dir);
			modelSetLED();
		}
		newRefresh();
	}
}

void modelDisplayInit(){
	isMsg = 0;
	isSnake = 1;
	ANSELB = 0;
	TRISB = TRISB | 0x2F80;
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setModelArray(0, i, j, k);
			}
		}
	}
}

void readModelFile(){
	// FILE *filePtr;
	uint8_t model[] = 
	{
		1, 1, 1,
		2, 1, 1, 
		3, 1, 1,
		4, 1, 1,
		5, 1, 1,
		1, 2, 2,
		1, 3, 3,
		2, 3, 3,
		3, 3, 3,
		4, 3, 3,
		5, 3, 3
	};
	uint8_t inputLev = 0;
	uint8_t inputRow = 0;
	uint8_t inputCol = 0;
	int i = 0;
	for(i = 0; i < /*(sizeof(model) / sizeof(model[0]))*/11; i++){
		uint8_t index = i * 3;
		inputLev = /*(uint8_t)*/model[index];
		inputRow = /*(uint8_t)*/model[index + 1];
		inputCol = /*(uint8_t)*/model[index + 2];
		setModelArray(1, inputLev, inputRow, inputCol);
	}
}

void modelSetLED(){
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
				thisRow += !!(getModelArray(i, j, k - 1));			
			}
			setArray(thisRow, i, j);
		}
	}
	changed = 1;
}

void rotate(uint8_t dir){
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				newModelArray[i][k][j] = 0;
			}
		}
	}
	
	if(dir == RIGHT){
		i = 0;
		j = 0;
		k = 0;
		for(i = 0; i < LEV_NUM; i++){
			for(j = 0; j < ROW_NUM; j++){
				for(k = 0; k < COL_NUM; k++){
					newModelArray[i][COL_NUM - k][j] = getModelArray(i, j, k);
				}
			}
		}
	}
	else if(dir == LEFT){
		i = 0;
		j = 0;
		k = 0;
		for(i = 0; i < LEV_NUM; i++){
			for(j = 0; j < ROW_NUM; j++){
				for(k = 0; k < COL_NUM; k++){
					newModelArray[i][k][ROW_NUM - j] = getModelArray(i, j, k);
				}
			}
		}
	}

	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setModelArray(newModelArray[i][j][k], i, j, k);
			}
		}
	}
}

void setModelArray(uint8_t isOn, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	modelArray[levIndex][rowIndex][colIndex] = isOn;
}

uint8_t getModelArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	return modelArray[levIndex][rowIndex][colIndex];
}