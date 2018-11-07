/**
 * If a certain LED is on:
 * ROW = 1, COL = 1, LEV = 1
 * 
 */

#include "led_control.h"

void ledInit(){
    int i = 0;
    int j = 0;
    for(i = 0; i < LEV_NUM; i++){
        for(j = 0; j < COL_NUM; j++){
            cuboidArray[i][j] = 0;
        }
    }
    for(i = 0; i < ROW_PIN_NUM; i++){
        rowOut[i] = 0;
    }
    for(i = 0; i < COL_PIN_NUM; i++){
        colOut[i] = 0;
    }
    for(i = 0; i < LEV_PIN_NUM; i++){
        levOut[i] = 0;
    }
    ledIndex = 0;
    isOn = 0;
}

void setArray(uint8_t thisRow, uint8_t colIndex, uint8_t levIndex){
    cuboidArray[levIndex][colIndex] = thisRow;
}

uint8_t getArray(uint8_t colIndex, uint8_t levIndex){
    return cuboidArray[levIndex][colIndex];
}

void refresh(){
	int i = 0;
	ledIndex = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		refreshRow();
		refreshCol();
		refreshLev();
		refreshLedStatus();
		// writeToPort();
		testPrintLedStatus();
		ledIndex++;	
	}
}

void refreshRow(){
	uint8_t rowIndex = (ledIndex / 8) % 8;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < ROW_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & rowIndex);
		rowOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshCol(){
	uint8_t colIndex = ledIndex % 8;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < COL_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & colIndex);
		colOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshLev(){
	uint8_t levIndex = ledIndex % 64;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < LEV_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & levIndex);
		levOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshLedStatus(){
	uint8_t colIndex = ledIndex % 8;
	uint8_t levIndex = ledIndex % 64;
	uint8_t rowIndex = (ledIndex / 8) % 8;
	uint8_t thisRow = getArray(colIndex, levIndex);
	uint8_t mask = 1 << rowIndex;
	isOn = !!(mask & thisRow);
}

void writeToPort(){
    
}

void testPrintLedStatus(){

}

void testPinOutputs(){
	
}



