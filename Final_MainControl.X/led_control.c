/**
 * If a certain LED is on:
 * ROW = 1, COL = 1, LEV = 1
 * LEV0 - RA0 - PIN2
 * LEV1 - RA1 - PIN3
 * LEV2 - RB0 - PIN4
 * LEV3 - RB1 - PIN5 - reserved
 * ROW0 - RB2 - PIN6
 * ROW1 - RB3 - PIN7
 * ROW2 - RA2 - PIN9
 * COL0 - RA3 - PIN10
 * COL1 - RB4 - PIN11
 * COL2 - RA4 - PIN12
 * isOn - RB5 - PIN14
 */

#include "led_control.h"

void ledInit(){
	if(ON_TEST == 0){
		ANSELA = 0;
	    ANSELB = 0;
	    TRISA = TRISA & 0b00000; 
	    TRISB  = TRISB & 0b000000;
    }
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

void setArray(uint8_t thisRow, uint8_t levIndex, uint8_t rowIndex){
    cuboidArray[levIndex][rowIndex] = thisRow;
}

uint8_t getArray(uint8_t levIndex, uint8_t rowIndex){
    return cuboidArray[levIndex][rowIndex];
}

void refresh(){
	int i = 0;
	ledIndex = 0;
	for(i = 0; i < 2; i++){
		refreshRow();
		refreshCol();
		refreshLev();
		// refreshLedStatus();
		// if(ON_TEST == 1)
		// 	testPinOutputs();			
		// else
			writeToPort();
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
	uint8_t levIndex = ledIndex / 64;
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
	uint8_t levIndex = ledIndex / 64;
	uint8_t rowIndex = (ledIndex / 8) % 8;
	uint8_t thisRow = getArray(levIndex, rowIndex);
	uint8_t mask = 1 << rowIndex;
	isOn = !!(mask & thisRow);
}

void writeToPort(){
    //assuming it is 8*8*8
    uint8_t portaOut = 0;
    uint8_t portbOut = 0;
    /*PORTA*/
    portaOut += colOut[2];
    portaOut <<= 1;
    portaOut += colOut[0];
    portaOut <<= 1;
    portaOut += rowOut[2];
    portaOut <<= 1;
    portaOut += levOut[1];
    portaOut <<= 1;
    portaOut += levOut[0];
    /*PORTB*/
    portbOut += isOn;
    portbOut <<= 1;
    portbOut += colOut[1];
    portbOut <<= 1;
    portbOut += rowOut[1];
    portbOut <<= 1;
    portbOut += rowOut[0];
    portbOut <<= 1;
    portbOut += 0; //reserved for LEV3
    portbOut <<= 1;
    portbOut += levOut[2];
   	PORTA = /*(PORTA & 0b00000) |*/ portaOut;
   	PORTB = /*(PORTB & 0b000000) |*/ portbOut;
}

/**
 * print out cuboid array for testing LED programs
 */
void testPrintLedStatus(){
	//setArray(0b01101101, 2, 2);
	uint8_t buffer[64];
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t k = 0;
	uint8_t mask = 0;
	sprintf(buffer, "\r\nCol 7  Col 0\r\n|      |\r\n");
	uart_write_string(buffer);
	for(i = LEV_NUM; i > 0; i--){
		for(j = ROW_NUM; j > 0 ; j--){
			uint8_t thisRow = getArray(i - 1, j - 1);
			for(k = COL_NUM; k > 0; k--){
				mask = 1 << (k - 1);
				uint8_t thisBit = !!(mask & thisRow);
				sprintf(buffer, "%d", thisBit);
				uart_write_string(buffer);
			}
			sprintf(buffer, " <- Row %d\r\n", j - 1);
			uart_write_string(buffer);
		}
		sprintf(buffer, "^ Level %d\r\n\n", i - 1);
		uart_write_string(buffer);
	}
	sprintf(buffer, "^      ^\r\nCol 7  Col 0\r\n");
	uart_write_string(buffer);
}

/**
 * Test rows, cols and levels pin outputs
 */
void testPinOutputs(){
	uint8_t buffer[64];
	uint8_t restoredRow = 0;
	uint8_t restoredCol = 0;
	uint8_t restoredLev = 0;
	uint32_t restoredIndex = 0;
	int isCorrect = 1;
	int i = 0;
	//restore decimal numbers from output arrays
	for(i = 0; i < ROW_PIN_NUM; i++){
		restoredRow += (rowOut[i] << i);
	}	
	for(i = 0; i < COL_PIN_NUM; i++){
		restoredCol += (colOut[i] << i);
	}
	for(i = 0; i < LEV_PIN_NUM; i++){
		restoredLev += (levOut[i] << i);
	}
	//calculate ledIndex based on output rows, cols and levels
	restoredIndex = (restoredRow * 8) + (restoredLev * 64) + restoredCol;
	if(ledIndex != restoredIndex){
		sprintf(buffer, "error: ledIndex %d, restoredIndex %d\r\n", ledIndex, restoredIndex);
		uart_write_string(buffer);
	}
	else{
		sprintf(buffer, "ledIndex %d correct!\r\n", ledIndex);
		uart_write_string(buffer);
	}
}

void runLedTests(){
	// uart_init();
	ledInit();
	// isOn = 1;
	// int i = 0;
 //    int j = 0;
 //    for(i = 0; i < LEV_NUM; i++){
 //        for(j = 0; j < COL_NUM; j++){
 //            setArray(0xFF, i, j)
 //        }
 //    }
	// refresh();
	
	while(1){
		rowOut[0] = 0;
		rowOut[1] = 0;
		rowOut[2] = 0;
		colOut[0] = 0;
		colOut[1] = 0;
		colOut[2] = 0;
		levOut[0] = 0;
		levOut[1] = 0;
		levOut[2] = 0;
		isOn = 1;
		writeToPort();
		rowOut[0] = 1;
		rowOut[1] = 0;
		rowOut[2] = 0;
		colOut[0] = 1;
		colOut[1] = 0;
		colOut[2] = 0;
		levOut[0] = 1;
		levOut[1] = 0;
		levOut[2] = 0;
		isOn = 1;
		writeToPort();
		rowOut[0] = 1;
		rowOut[1] = 1;
		rowOut[2] = 1;
		colOut[0] = 0;
		colOut[1] = 0;
		colOut[2] = 0;
		levOut[0] = 1;
		levOut[1] = 1;
		levOut[2] = 1;
		isOn = 1;
		writeToPort();

	}
}



