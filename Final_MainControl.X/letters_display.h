/**
 * This module is used to display concrete letters and numbers
 * 
 * 
 */

#ifndef LETTERS_DISPLAY_H
#define	LETTERS_DISPLAY_H
#include <stdio.h>
#include <stdlib.h>
//#include <plib.h>
#include "led_control.h"

#define DISPLAY_ARRAY_ROW_NUM 36
#define SCROLL_SEC 1

void decode(char c);
void testDecode();
void lettersDisplayInit();
void writeToLED();
void ledMapping(uint8_t rollingIndex);

//uint8_t ledArray [8][8];
uint8_t arrayCharIndex;
uint8_t scrollIndex;
uint8_t displayArray[DISPLAY_ARRAY_ROW_NUM]; //#char = row num / 6



#endif	/* LETTERS_DISPLAY_H */

