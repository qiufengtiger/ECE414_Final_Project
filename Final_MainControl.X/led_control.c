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

// volatile uint8_t input;
// void __ISR(0, ipl1auto) InterruptHandler(void){
// 	input = 1;
// 	mINT4ClearIntFlag();
// }

void delay_us(uint16_t input){
    T3CON = 0x8030;
    TMR3 = 0;
    uint16_t delay = (40 * input)/ 256;
    while(TMR3 < delay){
        //wait
    }
    TMR3 = 0;
}

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


    // mINT4SetIntPriority(1);
    // INTEnableSystemSingleVectoredInt();
    // mINT4IntEnable(1);
    // input = 0;
}

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

void refresh(){
	int i = 0;
	ledIndex = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		ledIndex = i;
		refreshRow();
		refreshCol();
		refreshLev();
		refreshLedStatus();
		// if(ON_TEST == 1)
		// 	testPinOutputs();			
		// else
		writeToPort();
		delay_us(1000);
	}
}

void snakeWriteToList(){
	uint32_t i = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		onLEDlist[i] = 0;
	}
	// uint32_t listIndex = 0;
	listIndex = 0;
	for(i = 0; i < TOTAL_LED_NUM; i++){
		ledIndex = i;
		rowIndex = (ledIndex / 8) % 8;
		colIndex = ledIndex % 8;
		levIndex = ledIndex / 64;
		uint8_t thisRow = getArray(levIndex, rowIndex);
		uint8_t mask = 1 << colIndex;
		uint8_t on = !!(mask & thisRow);
		if(on){
			onLEDlist[listIndex] = ledIndex;
			listIndex++;
		}
	}
	// onLEDlist[0] = 3;
	// onLEDlist[1] = 4;
	// onLEDlist[2] = 5;
	// listIndex = 3;
}

void newRefresh(){
	uint8_t on = 0;
	uint32_t i = 0;
	
	// ledIndex = 0;
	if(isMsg == 1){
		for(i = 0; i < TOTAL_LED_NUM; i++){
		if(isMsg && i % 64 < 39) continue;
			ledIndex = i;
			rowIndex = (ledIndex / 8) % 8;
			colIndex = ledIndex % 8;
			levIndex = ledIndex / 64;
			uint8_t thisRow = getArray(levIndex, rowIndex);
			uint8_t mask = 1 << colIndex;
			on = !!(mask & thisRow);
			if(on == 1){
				refreshRow();
				refreshCol();
				refreshLev();
				writeToPort();
			}
			on = 0;
		}
	}
	else if(isSnake == 1){
		if(changed){
			// listIndex = 0;
			// for(i = 0; i < TOTAL_LED_NUM; i++){
			// 	onLEDlist[i] = 0;
			// }
			// for(i = 0; i < TOTAL_LED_NUM; i++){
			// 	ledIndex = i;
			// 	rowIndex = (ledIndex / 8) % 8;
			// 	colIndex = ledIndex % 8;
			// 	levIndex = ledIndex / 64;
			// 	uint8_t thisRow = getArray(levIndex, rowIndex);
			// 	uint8_t mask = 1 << colIndex;
			// 	uint8_t on = !!(mask & thisRow);
			// 	if(on){
			// 		onLEDlist[listIndex] = ledIndex;
			// 		listIndex++;
			// 	}
			// 	on = 0;
			// }
			snakeWriteToList();
			changed = 0;
		}
		for(i = 0; i < listIndex; i++){
			ledIndex = onLEDlist[i];
			rowIndex = (ledIndex / 8) % 8;
			colIndex = ledIndex % 8;
			levIndex = ledIndex / 64;
			refreshRow();
			refreshCol();
			refreshLev();
			writeToPort();
			// ledIndex = 0;
		}
	}
	
	// onLEDlist[listIndex] = 0xFFFFFFFF; //end of list
	
	
	
}

void refreshRow(){
	rowIndex = (ledIndex / 8) % 8;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < ROW_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & rowIndex);
		rowOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshCol(){
	colIndex = ledIndex % 8;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < COL_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & colIndex);
		colOut[i] = thisBit;
		mask <<= 1;
	}
}

void refreshLev(){
	levIndex = ledIndex / 64;
	int i = 0;
	uint8_t mask = 1;
	for(i = 0; i < LEV_PIN_NUM; i++){
		uint8_t thisBit = !!(mask & levIndex);
		levOut[i] = thisBit;
		mask <<= 1;
	}   
}
void refreshLedStatus(){
	uint8_t thisRow = getArray(levIndex, rowIndex);
	uint8_t mask = 1 << colIndex;
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

    // /*switch row & col*/ 
    // portaOut += rowOut[2];
    // portaOut <<= 1;
    // portaOut += rowOut[0];
    // portaOut <<= 1;
    // portaOut += colOut[2];
    // portaOut <<= 1;
    // portaOut += levOut[1];
    // portaOut <<= 1;
    // portaOut += levOut[0];
    // /*PORTB*/
    // portbOut += isOn;
    // portbOut <<= 1;
    // portbOut += rowOut[1];
    // portbOut <<= 1;
    // portbOut += colOut[1];
    // portbOut <<= 1;
    // portbOut += colOut[0];
    // portbOut <<= 1;
    // portbOut += 0; //reserved for LEV3
    // portbOut <<= 1;
    // portbOut += levOut[2];

    // portaOut += !!colOut[2];
    // portaOut <<= 1;
    // portaOut += !!colOut[0];
    // portaOut <<= 1;
    // portaOut += !!rowOut[2];
    // portaOut <<= 1;
    // portaOut += levOut[1];
    // portaOut <<= 1;
    // portaOut += levOut[0];
    // /*PORTB*/
    // portbOut += !!isOn;
    // portbOut <<= 1;
    // portbOut += !!colOut[1];
    // portbOut <<= 1;
    // portbOut += !!rowOut[1];
    // portbOut <<= 1;
    // portbOut += !!rowOut[0];
    // portbOut <<= 1;
    // portbOut += !!0; //reserved for LEV3
    // portbOut <<= 1;
    // portbOut += levOut[2];


   	PORTA = (PORTA & 0b00000) | portaOut;
   	delay_us(1);
   	PORTB = (PORTB & 0b000000) | portbOut;
   	// delay_us(500000);
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
	// ledInit();
	// // // 	rowOut[0] = 0;
	// // // 	rowOut[1] = 0;
	// // // 	rowOut[2] = 0;
	// // // 	colOut[0] = 0;
	// // // 	colOut[1] = 0;
	// // // 	colOut[2] = 0;
	// // // 	levOut[0] = 0;
	// // // 	levOut[1] = 0;
	// // // 	levOut[2] = 0;
	// // // isOn = 1;
	// // int i = 0;
	// // int j = 0;
 // //    for(i = 0; i < LEV_NUM; i++){
 // //        for(j = 0; j < ROW_NUM; j++){
 // //        	// if(i % 2 == 1)
 // //         //    	setArray(0b00000000, i, j);
 // //         //    else
 // //            	setArray(0b10000000, i, j);
 // //        }
 // //    }
	// // isOn = 1;
	// // setArray(0b11111111, 0, 0);
	// // setArray(0b11001100, 1, 0);
	// // // int i = 0;
	// 	uint8_t buffer[64]; 
	// while(1){
	// 	if(input == 1){
	// 		sprintf(buffer, "hhhhhhh");
	// 		uart_write_string(buffer);
	// 	}
		 // refresh();
		// newRefresh();
	// 	// writeToPort();
	// }
	
	
		// ledIndex = 9;
		// refreshRow();
		// refreshLev();
		// refreshCol();
	// setArray(11111111, 0, 0);
	// refreshLedStatus();
	
	// writeToPort();
	// refresh();
	// int n = 0;
	// while(1){
		// while(n < 8){
		// 	refreshRow();
		// refreshCol();
		// refreshLev();
		// refreshLedStatus();
		// writeToPort();
		// 	// n++;
		// // }
		// // n = 0;
		// if(ledIndex == TOTAL_LED_NUM){
		// 	ledIndex = 0;
		// }
		// else ledIndex ++;
		// rowOut[0] = 0;
		// rowOut[1] = 0;
		// rowOut[2] = 1;
		// colOut[0] = 0;
		// colOut[1] = 0;
		// colOut[2] = 1;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 0;
		// isOn = 1;
		// writeToPort();
		// rowOut[0] = 1;
		// rowOut[1] = 0;
		// rowOut[2] = 0;
		// colOut[0] = 0;
		// colOut[1] = 1;
		// colOut[2] = 0;
		// levOut[0] = 1;
		// levOut[1] = 1;
		// levOut[2] = 0;
		// isOn = 1;
		// writeToPort();
		// rowOut[0] = 0;
		// rowOut[1] = 0;
		// rowOut[2] = 1;
		// colOut[0] = 0;
		// colOut[1] = 0;
		// colOut[2] = 1;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 1;
		// isOn = 1;
		// writeToPort();

		
		// rowOut[0] = 0;
		// rowOut[1] = 0;
		// rowOut[2] = 0;
		// colOut[0] = 0;
		// colOut[1] = 0;
		// colOut[2] = 0;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 0;
		// // refresh();

		// refreshLedStatus();
		// writeToPort();

		// rowOut[0] = 1;
		// rowOut[1] = 0;
		// rowOut[2] = 0;
		// colOut[0] = 1;
		// colOut[1] = 0;
		// colOut[2] = 0;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 0;
		// refreshLedStatus();
		// writeToPort();
		// rowOut[0] = 0;
		// rowOut[1] = 1;
		// rowOut[2] = 0;
		// colOut[0] = 0;
		// colOut[1] = 1;
		// colOut[2] = 0;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 0;
		// refreshLedStatus();
		// writeToPort();


		// rowOut[0] = 1;
		// rowOut[1] = 1;
		// rowOut[2] = 0;
		// colOut[0] = 1;
		// colOut[1] = 1;
		// colOut[2] = 0;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 0;
		// refreshLedStatus();
		// writeToPort();
		// rowOut[0] = 0;
		// rowOut[1] = 0;
		// rowOut[2] = 1;
		// colOut[0] = 0;
		// colOut[1] = 0;
		// colOut[2] = 1;
		// levOut[0] = 0;
		// levOut[1] = 0;
		// levOut[2] = 1;
		// isOn = 1;
		// writeToPort();
		// rowOut[0] = 1;
		// rowOut[1] = 0;
		// rowOut[2] = 1;
		// colOut[0] = 1;
		// colOut[1] = 0;
		// colOut[2] = 1;
		// levOut[0] = 1;
		// levOut[1] = 0;
		// levOut[2] = 1;
		// isOn = 1;
		// writeToPort();
		// rowOut[0] = 0;
		// rowOut[1] = 1;
		// rowOut[2] = 1;
		// colOut[0] = 0;
		// colOut[1] = 1;
		// colOut[2] = 1;
		// levOut[0] = 0;
		// levOut[1] = 1;
		// levOut[2] = 1;
		// isOn = 1;
		// writeToPort();
		// rowOut[0] = 1;
		// rowOut[1] = 1;
		// rowOut[2] = 1;
		// colOut[0] = 1;
		// colOut[1] = 1;
		// colOut[2] = 1;
		// levOut[0] = 1;
		// levOut[1] = 1;
		// levOut[2] = 1;
		// isOn = 1;
		// writeToPort();

	// }
}





