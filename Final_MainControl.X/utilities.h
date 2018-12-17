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

uint8_t joystickDirY;
uint8_t joystickDirX;
uint8_t outputDir;
uint8_t outputDirLock = 0;
uint8_t levelToPulse = 0;

uint8_t upButtonState;
uint8_t downButtonState;
uint8_t buttonPressed;

uint8_t tabSelected;

static void checkJoystickDir(){
	uint8_t buffer[64];
	uint8_t inputDirY = NOT_AVAILABLE;
	uint8_t inputDirX = NOT_AVAILABLE;
	uint16_t inputY = analog_in_read(9);//AN5, PIN7
	uint16_t inputX = analog_in_read(11);//AN11, PIN24
	if(inputY > 700)
		inputDirY = FORWARD;
	else if(inputY < 340)
		inputDirY = BACKWARD;
	else
		inputDirY = NOT_AVAILABLE;

	if(inputX > 700)
		inputDirX = RIGHT;
	else if(inputX < 340)
		inputDirX = LEFT;
	else
		inputDirX = NOT_AVAILABLE;
	if(/*!gameover && (*/tabSelected == 2 | tabSelected == 3/*)*/){
		// if(inputDirY != joystickDirY)
		// {
			// joystickDirY = inputDirY;
			if(outputDirLock == 0 && inputDirY != NOT_AVAILABLE){
				outputDir = inputDirY;
				outputDirLock = 1;
			}
		// }	
		// if(inputDirX != joystickDirX)
		// {
			// joystickDirX = inputDirX;
			if(outputDirLock == 0 && inputDirX != NOT_AVAILABLE){
				outputDir = inputDirX;
				outputDirLock = 1;
			}
		// }	
	}
}

static void checkButtonsDir(){
	uint8_t buffer[64];
	uint16_t forwardInput = !!(PORTB & 0x80);// RB7, PIN16
	uint16_t backwardInput = !!(PORTB & 0x100);// RB8, PIN17
	uint16_t leftInput = !!(PORTB & 0x200);// RB9, PIN18
	uint16_t rightInput = !!(PORTB & 0x400);// RB10, PIN21
	uint16_t upInput = !!(PORTB & 0x800);// RB11, PIN22
	uint16_t downInput = !!(PORTB & 0x2000); //RB13, PIN24 
	if(forwardInput == 1){

	}
	else if(backwardInput == 1){

	}
	else if(leftInput == 1){

	}
	else if(rightInput == 1){

	}
	else if(upInput == 1){

	}
	else if(downInput == 1){

	}
	else{

	}
	// if(upInput != upButtonState && buttonPressed == DEFAULT &&  (tabSelected == 2 | tabSelected == 3)){
	// 	buttonPressed = UP;
	// 	TMR1 = 0;
	// }
	// else if(downInput != downButtonState && buttonPressed == DEFAULT &&  (tabSelected == 2 | tabSelected == 3)){
	// 	buttonPressed = DOWN;
	// 	TMR1 = 0;
	// }
	// if(/*TMR1 > 5000*//*!gameover && (*/tabSelected == 2 | tabSelected == 3/*)*/){
	// 	if(buttonPressed == UP){
	// 		upButtonState = 1;
	// 	}
	// 	else if(buttonPressed == DOWN){
	// 		downButtonState = 1;
	// 	}
	// 	else{
	// 		upButtonState = 0;
	// 		downButtonState = 0;
	// 	}
	// }
	if((tabSelected == 2 | tabSelected == 3)/* && outputDirLock == 0*//* && buttonPressed != NOT_AVAILABLE*/){
		outputDir = buttonPressed;
		outputDirLock = 1;
	}
}

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
	// else if(levelToPulse == 1 && outputDir == NOT_AVAILABLE){
	// 	levelToPulse = 0;
	// }
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

