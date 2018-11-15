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
#define DISPLAY_ARRAY_ROW_NUM (DISPLAY_ROW_NUM + LEV_NUM)
#define SCROLL_MSEC 3000

void decode(char c);
void decodeArray(char c[]);
void lettersDisplayInit();
void writeToLED();
void ledMapping(uint8_t rollingIndex);

//uint8_t ledArray [8][8];
uint8_t arrayCharIndex;
uint8_t scrollIndex;
uint8_t displayArray[DISPLAY_ARRAY_ROW_NUM]; //#char = row num / 6
													   //add additional LEV_NUM for display effect

/*test methods*/
void testDecode();
void runLettersDisplayTests();

#endif	/* LETTERS_DISPLAY_H */

