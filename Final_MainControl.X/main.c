#include "led_control.h"
#include "letters_display.h"
#include "snake.h"
#include "robot.h"
#include "utilities.h"

// Configure clocks
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF



void main(){
	ANSELB = 0;
	TRISB = TRISB | 0xC000; //for input from touchscreen
	tabSelected = 1;
	loop:
	//choose module based on tabSelected
	switch(tabSelected){
		case 1:
			runLettersDisplay();
			break;
		case 2:
			runSnakeGame();
			break;
		case 3:
			//remove robot game
			runLettersDisplay();
			break;
		case 4:
			runModelDisplay();
			break;
		default:
			tabSelected = 1;
			break;
	}
	goto loop;
}
