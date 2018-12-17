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

#define NOT_AVAILABLE 0
#define FORWARD       1
#define BACKWARD      2
#define LEFT 	      3
#define RIGHT 		  4
#define UP 			  5
#define DOWN 		  6
#define DEFAULT 	  7

typedef struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	uint8_t type;
} pt;

uint8_t outputDir;
uint8_t levelToPulse = 0;
uint8_t tabSelected;

static uint8_t checkDir(){
	// uint16_t portBInput = PORTB;
	uint16_t forwardInput = !!(PORTB & 0x80);// RB7, PIN16
	uint16_t backwardInput = !!(PORTB & 0x100);// RB8, PIN17
	uint16_t leftInput = !!(PORTB & 0x200);// RB9, PIN18
	uint16_t rightInput = !!(PORTB & 0x400);// RB10, PIN21
	uint16_t upInput = !!(PORTB & 0x800);// RB11, PIN22
	uint16_t downInput = !!(PORTB & 0x2000); //RB13, PIN24 
	if(forwardInput == 1){
		outputDir = FORWARD;
	}
	else if(backwardInput == 1){
		outputDir = BACKWARD;	
	}
	else if(leftInput == 1){
		outputDir = LEFT;
	}
	else if(rightInput == 1){
		outputDir = RIGHT;
	}
	else if(upInput == 1){
		outputDir = UP;
	}
	else if(downInput == 1){
		outputDir = DOWN;
	}
	else{
		outputDir = NOT_AVAILABLE;
	}
	if(levelToPulse == 0){
		levelToPulse = 1;
		return outputDir;
	}
	else if(outputDir == NOT_AVAILABLE){
		levelToPulse = 0;
		// return ;
	}
	return 0;
}





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
	CNPUB = 0xC000;
	uint8_t inputCode0 = !!(PORTB & 0x4000);
	uint8_t inputCode1 = !!(PORTB & 0x8000);
	uint8_t newTabSelected = tabSelected;
 	if(inputCode1 == 0 && inputCode0 == 0) newTabSelected = 1;
 	else if(inputCode1 == 0 && inputCode0 == 1) newTabSelected = 2;
 	else if(inputCode1 == 1 && inputCode0 == 0) newTabSelected = 3;
 	else if(inputCode1 == 1 && inputCode0 == 1) newTabSelected = 4;
 	else newTabSelected = 0;
 	if(newTabSelected != tabSelected){
 		tabSelected = newTabSelected;
 		return 1;
 	}
 	else
 		return 0;
}

#endif	/* UTILITIES_H */

