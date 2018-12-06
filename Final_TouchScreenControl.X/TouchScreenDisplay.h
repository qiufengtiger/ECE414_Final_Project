/* 
 * File:   TouchScreenDisplay.h
 * Author: qiuf
 *
 * Created on December 2, 2018, 9:31 PM
 */

#ifndef TOUCHSCREENDISPLAY_H
#define	TOUCHSCREENDISPLAY_H

#include "Adafruit_2_4_LCD_Serial_Library\tft_master.h"
#include "Adafruit_2_4_LCD_Serial_Library\tft_gfx.h"
#include "TouchScreen.h"
#include <stdlib.h>
#include <inttypes.h>

// #define DW          360
// #define DH          240
// #define RED         0b1111100000000000
// #define GREEN       0b0000011111100000
// #define BLUE        0b0000000000011111
// #define YELLOW      0b1111111111100000
#define BLACK       0b0000000000000000
#define WHITE       0b1111111111111111
#define GRAY        0b0111101111101111

uint16_t tabMsgColor;
uint16_t tabSnakeColor;
uint16_t tabRobotColor;
uint16_t tabModelColor;
uint8_t tabSelected;
uint16_t tabTextColor;

void runTouchScreenDisplay();
uint16_t touchMappingX(uint16_t y);
uint16_t touchMappingY(uint16_t x);
void TabsRefresh();
void selectTab(uint8_t index);
void runMsgContent();
void runSnakeContent();
void runRobotContent();
void runModelContent();
uint8_t detectTouch();
void runButtons(uint8_t button);
void checkGameover();


/*test methods*/
void runTouchScreenDisplayTests();


#endif	/* TOUCHSCREENDISPLAY_H */

