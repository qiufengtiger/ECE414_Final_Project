/* 
 * File:   model_display.h
 * Author: qiuf
 *
 * Created on December 15, 2018, 7:56 PM
 */

#ifndef MODEL_DISPLAY_H
#define	MODEL_DISPLAY_H
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"
#include "utilities.h"

uint8_t modelArray[LEV_NUM][ROW_NUM][COL_NUM]; 
uint8_t newModelArray[LEV_NUM][COL_NUM][ROW_NUM];

void runModelDisplay();
void modelDisplayInit();
void readModelFile();
void modelSetLED();
void rotate(uint8_t dir);
void setModelArray(uint8_t isOn, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);
uint8_t getModelArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex);

#endif	/* MODEL_DISPLAY_H */

