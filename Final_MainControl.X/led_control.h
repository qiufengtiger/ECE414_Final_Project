#ifndef LED_CONTROL_H
#define	LED_CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
//#include "utilities.h"

#define TEST 0
#define ROW_NUM 8
#define COL_NUM 8
#define LEV_NUM 8

#define ROW_PIN_NUM 3

uint8_t cuboidArray[LEV_NUM][COL_NUM];
uint8_t RowOut[ROW_PIN_NUM];



void ledInit();
void refresh();
void refreshRow();
void refreshCol();
void refreshLev();
void writeToPort();

void writeToArray(uint8_t thisRow, uint8_t colIndex, uint8_t levIndex);

//uint8_t logTwo(uint8_t input);

/*test methods*/
void printArrayToUART();


#ifdef TEST



#endif

#endif	/* LED_CONTROL_H */

