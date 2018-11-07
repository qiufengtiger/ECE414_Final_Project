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
#include "led_control.h"

#define DISPLAY_ARRAY_SIZE 6

void decode(char c);
void testDecode();
void lettersDisplayInit();
void writeToLED();
void ledMapping(uint8_t rollingIndex);

//uint8_t ledArray [8][8];
uint8_t arrayCharIndex;
uint8_t rollingIndex;
uint8_t displayArray[DISPLAY_ARRAY_SIZE * 6]; //DISPLAY_ARRAY_SIZE * 6 rows



#endif	/* LETTERS_DISPLAY_H */

