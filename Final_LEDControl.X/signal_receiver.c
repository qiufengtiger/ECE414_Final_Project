/**
 * This module serves to receive 10 bits signal from the Main Control MCU.
 * It also decodes the signal into 4 bits levels, 3 bits rows and 3 bits cols
 * LEVEL4 bit is from Main Control since PIC32 only has 19 output pins 
 * inputs:                  Outputs:
 * (8 * 8 * 8)
 * 0 - RA0                  LEVEL0 - RA4
 * 1 - RA1                  LEVEL1 - RB5
 * 2 - RB0                  LEVEL2 - RB7
 * 3 - RB1                  ROW0   - RB8                  
 * 4 - RB2                  ROW1   - RB9
 * 5 - RB3                  ROW2   - RB10 
 * 6 - RA2                  COL0   - RB11 
 * 7 - RA3                  COL1   - RB13 
 * 8 - RB4                  COL2   - RB14
 *----------
 * joy0_x - RA0
 * joy0_y - RA1
 * joy1_x - RB0
 * joy1_y - RB1
 * Maybe we do not need this module
 */
#include "signal_receiver.h"

void signalInit(){
    ANSELA = 0;
    ANSELB = 0;
    //TRISA = 0b01111
    //TRISB = 0b000000000011111
    TRISA = 0x0F;
    TRISB = 0x001F;
}

void getSignals(){
    inputs[0] = PORTA & (0x0001 << 0);
    inputs[1] = PORTA & (0x0001 << 1);
    inputs[2] = PORTB & (0x0001 << 0);
    inputs[3] = PORTB & (0x0001 << 1);
    inputs[4] = PORTB & (0x0001 << 2);
    inputs[5] = PORTB & (0x0001 << 3);
    inputs[6] = PORTA & (0x0001 << 2);
    inputs[7] = PORTA & (0x0001 << 3);
    inputs[8] = PORTB & (0x0001 << 4);
}

void getRows(){
    
}

// output signals to hardware decoders
void outputToDec() {
	PORTA |= levels[0] << 4;
	PORTB |= levels[1] << 5;
	PORTB |= levels[2] << 7;
	PORTB |= rows[0] << 8;
	PORTB |= rows[1] << 9;
	PORTB |= rows[2] << 10;
	PORTB |= cols[0] << 11;
	PORTB |= cols[1] << 13;
	PORTB |= cols[2] << 14;
}

void getBtnJoy() {
	
}

