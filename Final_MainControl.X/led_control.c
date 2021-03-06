/**
 * This module is the LED driver
 * There are two modes of scanning: Msg and Snake. Model display also uses snake scanning.
 * LEV0 - RA0 - PIN2
 * LEV1 - RA1 - PIN3
 * LEV2 - RB0 - PIN4
 * LEV3 - RB1 - PIN5
 * ROW0 - RB2 - PIN6
 * ROW1 - RB3 - PIN7
 * ROW2 - RA2 - PIN9
 * COL0 - RA3 - PIN10
 * COL1 - RB4 - PIN11
 * COL2 - RA4 - PIN12
 */

#include "led_control.h"

void delay_us(uint16_t input){
    T3CON = 0x8030;
    TMR3 = 0;
    uint16_t delay = (40 * input)/ 256;
    while(TMR3 < delay){
        //wait
    }
    TMR3 = 0;
}

/**
 * Initialization
 * setup pins & cuboid array that other modules will write data to.
 */
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
    levIndex = 0;
    rowIndex = 0;
    colIndex = 0;
    isOn = 0;
    isMsg = 0;
    isSnake = 0;
    listIndex = 0;
    changed = 1;
}

/**
 * Clear data in cuboid array. Reset outputs.
 */ 
void resetLed(){
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
    levIndex = 0;
    rowIndex = 0;
    colIndex = 0;
    isOn = 0;
}

void setArray(uint8_t thisRow, uint8_t levIndex, uint8_t rowIndex){
    cuboidArray[levIndex][rowIndex] = thisRow;
}

uint8_t getArray(uint8_t levIndex, uint8_t rowIndex){
    return cuboidArray[levIndex][rowIndex];
}

/**
 * Refresh list that stores all "on" LED index. Used in snake scanning
 */ 
void snakeWriteToList(){
	uint32_t i = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		onLEDlist[i] = 0;
	}
	listIndex = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		ledIndex = i;
		//calculate row & col & lev number based on ledIndex
		rowIndex = (ledIndex / 8) % 8;
		colIndex = ledIndex % 8;
		levIndex = ledIndex / 64;
		uint8_t thisRow = getArray(levIndex, rowIndex);
		uint8_t mask = 1 << colIndex;
		//check if that bit is 1
		uint8_t on = !!(mask & thisRow);
		if(on){
			onLEDlist[listIndex] = ledIndex;
			listIndex++;
		}
	}
}

/**
 * Refresh LEDs based on scanning mode set.
 */ 
void newRefresh(){
	uint8_t on = 0;
	uint32_t i = 0;
	if(isMsg == 1){
		for(i = 0; i < TOTAL_LED_NUM; i++){
		    //skip LEDs that are not the last three rows because we only want to display Msgs on the last two rows. Provides faster scanning.
		    if(isMsg && i % 64 < 39) continue;
			ledIndex = i;
			rowIndex = (ledIndex / 8) % 8;
			colIndex = ledIndex % 8;
			levIndex = ledIndex / 64;
			uint8_t thisRow = getArray(levIndex, rowIndex);
			uint8_t mask = 1 << colIndex;
			on = !!(mask & thisRow);
			if(on == 1){
			    //refresh outputs
				refreshRow();
				refreshCol();
				refreshLev();
				writeToPort();
			}
			on = 0;
		}
	}
	else if(isSnake == 1){
	    //refresh "on" LED list only when other modules indicates so (changed set to 1)
		if(changed){
			snakeWriteToList();
			changed = 0;
		}
		//go through the "on" LED list
		for(i = 0; i < listIndex; i++){
			ledIndex = onLEDlist[i];
			rowIndex = (ledIndex / 8) % 8;
			colIndex = ledIndex % 8;
			levIndex = ledIndex / 64;
			refreshRow();
			refreshCol();
			refreshLev();
			writeToPort();
		}
	}
}

/**
 * Refresh output arrays
 */ 
void refreshRow(){
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < ROW_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & rowIndex);
		rowOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshCol(){
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < COL_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & colIndex);
		colOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshLev(){
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < LEV_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & levIndex);
		levOut[i] = thisBit;
		mask <<= 1;
	}   
}

/**
 * Write outputs to the circuit
 */ 
void writeToPort(){
    //please refer to the pin list at the top
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
    portbOut += levOut[3];
    portbOut <<= 1;
    portbOut += levOut[2];

   	PORTA = (PORTA & 0b00000) | portaOut;
   	PORTB = (PORTB & 0b000000) | portbOut;
}

/**
 * Print out cuboid array for testing LED programs
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
	// levIndex = 15;
	// rowIndex = 7;
	// colIndex = 0;
	// ledIndex = 511;
	isMsg = 0;
	isSnake = 1;
	changed = 0;
	// ledIndex = 1017;
	// rowIndex = ledIndex / 128;
	// colIndex = ledIndex % 8;
	// levIndex = ledIndex / 64;
	// changed = 1;
	// onLEDlist[0] = 1016;
	// onLEDlist[1] = 1018;
	// setArray(0b00011001, 10, 7);
	// cuboidArray[15][6] = 0b0001111;
	// onLEDlist[0] = 999;
	// listIndex = 1;
	snakeWriteToList();
	while(1){
		newRefresh();
	}
	// refreshLev();
	// refreshRow();
	// refreshCol();
	// writeToPort();

}





