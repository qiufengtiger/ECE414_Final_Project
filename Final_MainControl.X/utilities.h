/**
 * Functions shared by snake and robot
 */
#ifndef UTILITIES_H
#define	UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"

typedef struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	uint8_t type;
} pt;

 uint8_t tabSelected;

static uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	switch(dir){
		case 2: 
			if(rowIndex == 0) return 1; 
			else return 0;
		case 8:
			if(rowIndex == ROW_NUM - 1) return 1;
			else return 0;
		case 4:
			if(colIndex == COL_NUM - 1) return 1;
			else return 0;
		case 6:
			if(colIndex == 0) return 1;
			else return 0;
		case 1:
			if(levIndex == 0) return 1;
			else return 0;
		case 7:
			if(levIndex == LEV_NUM - 1) return 1;
			else return 0;
	}
	return 0;
}

static uint8_t absolute(uint8_t input){
	return (input >= 0 ? input : (input * -1));
}

/**
 * outputCode is from another PIC32 that controls all inputs
 * outputCode[0]: RB15, PIN26
 * outputCode[1]: RB14, PIN25
 * outputCode[2]: RB13, PIN24
 * outputCode[3]: RB11, PIN22
 * outputCode[4]: RB10, PIN21
 * return values: 0 => default, 1 => FORWARD, 2 => BACKWARD, 3 => LEFT, 4 => RIGHT
 * 5 => UP, 6 => DOWN, 7 => restart / selectTabs
 */
static uint8_t decodeFromInputControl(){
	uint8_t inputCode = 0;
	inputCode += !!(PORTB & 0x400);
	inputCode <<= 1;
	inputCode += !!(PORTB & 0x800);
	inputCode <<= 1;
	inputCode += !!(PORTB & 0x2000);
	inputCode <<= 1;
	inputCode += !!(PORTB & 0x4000);
	inputCode <<= 1;
	inputCode += !!(PORTB & 0x8000);
	switch(inputCode){
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		case 6:
			return 6;
		case 8:
			return 7;
		case 9:
			tabSelected = 1;
			return 7;
		case 10:
			tabSelected = 2;
			return 7;
		case 11:
			tabSelected = 3;
			return 7;
		case 12:
			tabSelected = 4;
			return 7;
		// case 10:
		// 	return 7;
		default:
			return 0;
	}
}

#endif	/* UTILITIES_H */

