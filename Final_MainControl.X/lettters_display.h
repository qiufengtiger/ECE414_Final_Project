/**
 * This module is used to display concrete letters and numbers
 * 
 * 
 */

#ifndef LETTTERS_DISPLAY_H
#define	LETTTERS_DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

void decode(char c, uint8_t charNum);
void testDecode();

//uint8_t ledArray [8][8];
uint8_t displayArray[32]; //32 rows

#endif	/* LETTTERS_DISPLAY_H */

