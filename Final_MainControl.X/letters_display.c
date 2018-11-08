#include "letters_display.h"


void lettersDisplayInit(){
    int i = 0;
    for(; i < DISPLAY_ARRAY_ROW_NUM; i ++){
        displayArray[i] = 0;
    }
    arrayCharIndex = 0;
    T1CON = 0x8030;
    TMR1 = 0;
}

void decode(char c){
    uint8_t line = arrayCharIndex * 6;
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
            displayArray[++line] = 0b00000000;//space
            break;
        case 'B':
            displayArray[line]   = 0b00101000;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
            break;
		case 'C':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case 'D':
			displayArray[line]   = 0b00111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'E':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'F':
			displayArray[line]   = 0b01000000;
            displayArray[++line] = 0b01000000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'G':
			displayArray[line]   = 0b01011100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00111000;
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
			displayArray[line]   = 0b01000000;
            displayArray[++line] = 0b01111000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00000000;
			break;
		case 'K':
			displayArray[line]   = 0b01000100;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'L':
			displayArray[line]   = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b00000100;
            displayArray[++line] = 0b01111100;
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
            displayArray[++line] = 0b00001000;
            displayArray[++line] = 0b00010000;
            displayArray[++line] = 0b00100000;
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
			displayArray[line]   = 0b00100000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'Q':
			displayArray[line]   = 0b00110100;
            displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case 'R':
			displayArray[line]   = 0b00101100;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01010000;
            displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b00000000;
			break;
		case 'S':
			displayArray[line]   = 0b01001000;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00100100;
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
            displayArray[++line] = 0b01100100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case '0':
			displayArray[line]   = 0b00111000;
			displayArray[++line] = 0b01100100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case '1':
			displayArray[line]   = 0b00000000;
			displayArray[++line] = 0b00000100;
			displayArray[++line] = 0b01111100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
            displayArray[++line] = 0b00000000;
			break;
		case '2':
			displayArray[line]   = 0b00100100;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01001100;
            displayArray[++line] = 0b00000000;
			break;
		case '3':
			displayArray[line]   = 0b00101000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b00000000;
			break;
		case '4':
			displayArray[line]   = 0b00001000;
			displayArray[++line] = 0b01111100;
			displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b00101000;
            displayArray[++line] = 0b00011000;
            displayArray[++line] = 0b00000000;
			break;
		case '5':
			displayArray[line]   = 0b01001000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01110100;
            displayArray[++line] = 0b00000000;
			break;
		case '6':
			displayArray[line]   = 0b01001000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00111000;
            displayArray[++line] = 0b00000000;
			break;
		case '7':
			displayArray[line]   = 0b01100000;
			displayArray[++line] = 0b01010000;
			displayArray[++line] = 0b01001000;
            displayArray[++line] = 0b01000100;
            displayArray[++line] = 0b01000000;
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
			displayArray[line]   = 0b00111000;
			displayArray[++line] = 0b01010100;
			displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b01010100;
            displayArray[++line] = 0b00100100;
            displayArray[++line] = 0b00000000;
			break;
    }
}

void setLED(){
    ledInit();
    if(SCROLL_SEC == 0){
        ledMapping(0);
    }
    else{
        uint32_t delay = (40000000 * SCROLL_SEC) / 256;
    scrollIndex = 0;
    while(TMR1 < delay){
        ledMapping(scrollIndex);
        if(scrollIndex == DISPLAY_ARRAY_ROW_NUM) 
            scrollIndex = 0;
        else
            scrollIndex ++;
        }
    }  
}

void ledMapping(uint8_t scrollIndex){
    uint8_t index = 0;
    for(index = 0; index < LEV_NUM; index++){
        if(index + scrollIndex > DISPLAY_ARRAY_ROW_NUM){
            setArray(00000000, 2, index);
            setArray(00000000, 3, index);
            setArray(00000000, 4, index);
            setArray(00000000, 5, index);
        }
        else{
            uint8_t thisRow = displayArray[index + scrollIndex];
//            uint8_t thisRow = 0;
            setArray(thisRow, 2, index);
            setArray(thisRow, 3, index);
            setArray(thisRow, 4, index);
            setArray(thisRow, 5, index);
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
    for(; j < DISPLAY_ARRAY_ROW_NUM; j++){
        sprintf(buffer, "%d\r\n", displayArray[j]);
//        sprintf(buffer, "test\r\n");
        uart_write_string(buffer);
    }
}

void runLettersDisplayTests(){
    lettersDisplayInit();
    decode('A');
    setLED();
    testPrintLedStatus();
}