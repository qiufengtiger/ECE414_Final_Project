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
	tabSelected = 2;
	loop:
	switch(tabSelected){
		case 1:
			runLettersDisplay();
			break;
		case 2:
			runSnakeGame();
			// runLettersDisplay();
			break;
		case 3:
			// runRobotGame();
			break;
		case 4:
			break;
		default:
			runLettersDisplay();
	}
	goto loop;

    // testDecode();
    // INT4R = 0x4;
    // runLedTests();
    // runLettersDisplayTests();
	// runSnakeTests();
	// runRobotTests();
	// runLettersDisplay();
	// runLedTests();
}
