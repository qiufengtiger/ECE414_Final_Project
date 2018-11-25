/**
 * Functions shared by snake and robot
 */
#ifndef UTILITIES_H
#define	UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include <p32xxxx.h>
#include "led_control.h"

typedef struct point{
	uint8_t lev;
	uint8_t row;
	uint8_t col;
	uint8_t type;
} pt;

static uint8_t isBorder(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	switch(dir){
		case 2: 
			if(rowIndex == 0) return 1; 
			else return 0;
		case 8:
			if(rowIndex == ROW_NUM - 1) return 1;
			else return 0;
		case 4:
			if(colIndex == COL_NUM - 1) return 1;
			else return 0;
		case 6:
			if(colIndex == 0) return 1;
			else return 0;
		case 1:
			if(levIndex == 0) return 1;
			else return 0;
		case 7:
			if(levIndex == LEV_NUM - 1) return 1;
			else return 0;
	}
	return 0;
}

#endif	/* UTILITIES_H */

