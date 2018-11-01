#include "lettters_display.h"

// Configure clocks
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF
/**
 * PIN:
 * LED Control: (8 * 8 * 8)
 * LEVEL0 - RA0
 * LEVEL1 - RA1
 * LEVEL2 - RB0
 * (LEVEL3 - RB1)
 * ROW0 - RB2
 * ROW1 - RB3
 * ROW2 - RA2
 * COL0 - RA3
 * COL1 - RB4
 * COL2 - RA4
 */
void main(){
    testDecode();
//    uart_init();
//    uart_write('t');
//    uart_init();
//    uint8_t buffer[64];
//    sprintf(buffer, "test\r\n");
//        uart_write_string(buffer);
}
