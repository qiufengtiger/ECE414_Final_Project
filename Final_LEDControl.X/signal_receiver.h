#ifndef SIGNAL_RECEIVER_H
#define	SIGNAL_RECEIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

void signalInit();
void getSignals();
void getLevels();
void getRows();
void getCols();

//stores input signals
uint8_t inputs[9]; 
//stores output signals
uint8_t levels[3];
uint8_t rows[3];
uint8_t cols[3];

#endif	/* SIGNAL_RECEIVER_H */

