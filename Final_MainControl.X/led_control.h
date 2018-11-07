#ifndef LED_CONTROL_H
#define	LED_CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>


#define TEST 0
#define ROW_NUM 1
#define COL_NUM 1
#define LEV_NUM 1

uint8_t cuboidArray[LEV_NUM][COL_NUM];

void refresh();
void refreshRow();
void refreshCol();
void refreshLev();
void writeToPort();

void writeToArray(uint8_t thisRow, uint8_t colIndex, uint8_t levIndex);

#ifdef TEST



#endif

#endif	/* LED_CONTROL_H */

