#include "TouchScreenDisplay.h"

// Configure clocks
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF




void main(int argc, char** argv) {
	runTouchScreenDisplayTests();
	// touchScreenParamInit();
 //    sendToMainControl(0, 0, 2);
}



