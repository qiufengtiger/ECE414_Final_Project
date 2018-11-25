#ifndef LED_CONTROL_H
#define	LED_CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
// #include "utilities.h"

#define ROW_NUM 8
#define COL_NUM 8
#define LEV_NUM 8
#define TOTAL_LED_NUM (ROW_NUM * COL_NUM * LEV_NUM)
#define ROW_PIN_NUM 3 //log2(ROW_NUM)
#define COL_PIN_NUM 3
#define LEV_PIN_NUM 3

#define ON_TEST 1

uint8_t cuboidArray[LEV_NUM][ROW_NUM];
uint8_t rowOut[ROW_PIN_NUM];
uint8_t colOut[COL_PIN_NUM];
uint8_t levOut[LEV_PIN_NUM];
uint32_t ledIndex;
uint8_t isOn;

void ledInit();
void refresh();
void refreshRow();
void refreshCol();
void refreshLev();
void refreshLedStatus();
void writeToPort();

void setArray(uint8_t thisRow, uint8_t colIndex, uint8_t levIndex);
uint8_t getArray(uint8_t rowIndex, uint8_t levIndex);

//uint8_t logTwo(uint8_t input);

/*test methods*/
void testPrintLedStatus();
void testPinOutputs(); 
void runLedTests();

#endif	/* LED_CONTROL_H */

