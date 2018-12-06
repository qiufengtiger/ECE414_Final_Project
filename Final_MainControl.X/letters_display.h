/**
 * This module is used to display concrete letters and numbers
 * 
 * 
 */

#ifndef LETTERS_DISPLAY_H
#define	LETTERS_DISPLAY_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"

#define DISPLAY_CHAR_NUM 4
#define DISPLAY_ROW_NUM (DISPLAY_CHAR_NUM * 6)
// #define DISPLAY_ARRAY_ROW_NUM (DISPLAY_ROW_NUM + LEV_NUM)
#define DISPLAY_ARRAY_ROW_NUM 32
#define SCROLL_MSEC 500

//uint8_t ledArray [8][8];
uint8_t arrayCharIndex;
uint8_t scrollIndex;
//#char = row num / 6
//add additional LEV_NUM for display effect
uint8_t displayArray[DISPLAY_ARRAY_ROW_NUM]; 

void runLettersDisplay();
void decode(char c);
void decodeArray(char c[]);
void lettersDisplayInit();
void writeToLED();
void setLED();
void ledMapping(uint8_t scrollIndex);

/*test methods*/
void testDecode();
void runLettersDisplayTests();

#endif	/* LETTERS_DISPLAY_H */

