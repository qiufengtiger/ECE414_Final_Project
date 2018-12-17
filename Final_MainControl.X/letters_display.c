#include "letters_display.h"

//interrupt timer for scrolling effect 
volatile uint32_t timer_ms_count;
void __ISR(0, ipl1auto) InterruptHandler(void){
    timer_ms_count++;
    mT1ClearIntFlag();
}

void runLettersDisplay(){
    ledInit();
    lettersDisplayInit();
    //Change display text here!
    //Please also change DISPLAY_CHAR_NUM in the header
    decodeArray("ECE414");
    while(1){
        //check if the function is changed through the touchscreen
        uint8_t input = decodeFromInputControl();
        if(input == 1)
            break;
        setLED();
        newRefresh();
    }
}

/**
 * Initialization. Initialize display array and also setup the timer 
 * 
 */ 
void lettersDisplayInit(){
    int i = 0;
    for(i = 0; i < DISPLAY_ARRAY_ROW_NUM; i++){
        displayArray[i] = 0b00000000;
    }
    arrayCharIndex = 0;
    scrollIndex = 0;
    T1CON = 0x8010; // interrupt
    TMR1 = 0;
    PR1 = 0x1000;
    mT1SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
    mT1IntEnable(1);
    timer_ms_count = 0;
    isMsg = 1;
    isSnake = 0;
}

/**
 * Decode a single character
 */ 
void decode(char c){
    //add LEV_NUM lines before everything since we want texts to start scrolling from the right
    uint8_t line = arrayCharIndex * 6 + LEV_NUM;
    arrayCharIndex ++;
    switch(c){
        case 'A':
            //line4 ooxxx
            //line3 oxoxo
            //line2 xooxo
            //line1 oxoxo
            //line0 ooxxx
            displayArray[line]   = 0b00011100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00011100;
            displayArray[++line] = 0b00000000;
            break;
        case 'B':
            displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00000000;
            break;
		case 'C':
			displayArray[line]   = 0b00111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'D':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case 'E':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'F':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b00000000;
			break;
		case 'G':
			displayArray[line]   = 0b00111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01011100;
            displayArray[++line] = 0b00000000;
			break;
		case 'H':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'I':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'J':
			displayArray[line]   = 0b01001000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01111000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b00000000;
			break;
		case 'K':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'L':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'M':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'N':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'O':
			displayArray[line]   = 0b00111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case 'P':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b00000000;
			break;
		case 'Q':
			displayArray[line]   = 0b00111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00110100;
            displayArray[++line] = 0b00000000;
			break;
		case 'R':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b00101100;
            displayArray[++line] = 0b00000000;
			break;
		case 'S':
			displayArray[line]   = 0b00100100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00000000;
			break;
		case 'T':
			displayArray[line]   = 0b01000000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b00000000;
			break;
		case 'U':
			displayArray[line]   = 0b01111000;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b01111000;
            displayArray[++line] = 0b00000000;
			break;
		case 'V':
			displayArray[line]   = 0b01110000;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b01110000;
            displayArray[++line] = 0b00000000;
			break;
		case 'W':
			displayArray[line]   = 0b01111100;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'X':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case 'Y':
			displayArray[line]   = 0b01000000;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b00011100;
            displayArray[++line] = 0b00100000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b00000000;
			break;
		case 'Z':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b01001100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01100100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case '0':
			displayArray[line]   = 0b00111000;
			displayArray[++line] = 0b01001100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01100100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case '1':
			displayArray[line]   = 0b00000000;
			displayArray[++line] = 0b01000100;
			displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
			break;
		case '2':
			displayArray[line]   = 0b01001100;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00100100;
            displayArray[++line] = 0b00000000;
			break;
		case '3':
			displayArray[line]   = 0b01000100;
			displayArray[++line] = 0b01000100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00000000;
			break;
		case '4':
			displayArray[line]   = 0b00011000;
			displayArray[++line] = 0b00101000;
			displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b00000000;
			break;
		case '5':
			displayArray[line]   = 0b01110100;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00000000;
			break;
		case '6':
			displayArray[line]   = 0b00111000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00000000;
			break;
		case '7':
			displayArray[line]   = 0b01000000;
			displayArray[++line] = 0b01000100;
			displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01100000;
            displayArray[++line] = 0b00000000;
			break;
		case '8':
			displayArray[line]   = 0b00101000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00000000;
			break;
		case '9':
			displayArray[line]   = 0b00100100;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
        default:
            displayArray[line]   = 0b00000000;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
            break;
    }
}

/**
 * Decode a string. Write all the data to the display array
 */ 
void decodeArray(char c[]){
    int i = 0;
    for(i = 0; i < DISPLAY_CHAR_NUM; i++){
        decode(c[i]);
    }
}

/**
 * Setup LED mapping. 
 * If SCROLL_SEC = 0, no scrolling is applied
 * Else, increment scrollingIndex for mapping
 */ 
void setLED(){
    if(SCROLL_MSEC == 0){
        ledMapping(0);
    }
    else{
        if(timer_ms_count < SCROLL_MSEC){
            //wait
        }
        else{
            timer_ms_count = 0;
            ledMapping(scrollIndex);
            //reset scrollingIndex when reaches the end
            if(scrollIndex == DISPLAY_ARRAY_ROW_NUM - 1) 
                scrollIndex = 0;
            else
                scrollIndex ++;
        }
        
    }
}

/**
 * Read data from display array and send to cuboid array in the driver
 */ 
void ledMapping(uint8_t scrollIndex){
    uint8_t index = 0;
    for(index = 0; index < LEV_NUM; index++){
        //if out of bound, goes back
        if(index + scrollIndex >= DISPLAY_ARRAY_ROW_NUM){
            uint8_t thisRow = displayArray[index + scrollIndex - DISPLAY_ARRAY_ROW_NUM];
            //set to last three rows
            setArray(thisRow, index, 5);
            setArray(thisRow, index, 6);
            setArray(thisRow, index, 7);
        }
        else{
            uint8_t thisRow = displayArray[index + scrollIndex];
            setArray(thisRow, index, 5);
            setArray(thisRow, index, 6);
            setArray(thisRow, index, 7);
        }
    }
}

void testDecode(){
    char test[] = "ABABAB";
    int i = 0;
    uint8_t buffer[64];
    
    uart_init();
    lettersDisplayInit();
    while(1){
        char c = test[i];
        
        if(c == 0) break;
        sprintf(buffer, "%c\r\n", c);
        uart_write_string(buffer);
        decode(c);
        i++;    
    }
    int j = 0;
    for(j = 0; j < DISPLAY_ARRAY_ROW_NUM; j++){
        sprintf(buffer, "%d\r\n", displayArray[j]);
        uart_write_string(buffer);
    }
}

void runLettersDisplayTests(){
    uart_init();
	// test case 1: decode one character
    lettersDisplayInit();
    // decode('A');
    decodeArray("TEST");
    while(1){
        setLED();
        testPrintLedStatus();     
    }
    
	// test case 2: decode several characters
	// lettersDisplayInit();
	// char test[] = "ABCA8";
	// int i = 0;
 //    for (i = 0; i < sizeof(test) / sizeof(test[0]) - 1; i++) {
	// 	decode(test[i]);
	// }
 //    setLED();
 //    testPrintLedStatus();
}