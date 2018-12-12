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
	// uart_init();
	// uint8_t buffer[64];
	// while(1){

	// 	char input = uart_read_nb();
	// 	if(input != 0){
	// 		sprintf(buffer, "hhhhhhh");
	// 		uart_write_string(buffer);
	// 	}
	// 	else{
	// 		sprintf(buffer, "aaaaaaa");
	// 		uart_write_string(buffer);
	// 	}
	// }


	/*UART U2 setup*/
	// uartDecodeFromInputControlInit();
	// ANSELA = 0;
 //    ANSELB = 0;
	// RPB9R = 0x2;
	// U2RXR = 0x4;
	// TRISB = TRISB | 0b1100000000;

	// U2BRG = 260; //40000000/(16 * 9600) - 1
 //    U2STA = U2STA | 0x1400;//URXEN
 //    U2MODE = U2MODE & 0b0111; //set slow mode
 //    U2MODE = U2MODE | 0x8000;//ON
	// uint8_t buffer[64];
	// while(1){
	// 	char input = uartDecodeFromInputControl();
	// 	// char input = uart_read_nb_2();
	// 	// sprintf(buffer, "%d", input);
	// 		// uart_write_string_2(buffer);
	// }


	tabSelected = 2;
	// // ANSELB = 0;
	// // TRISB = TRISB | 0xEC00;// for decodeFromInputControl
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
