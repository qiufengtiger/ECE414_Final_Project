#include "letters_display.h"


void lettersDisplayInit(){
    int i = 0;
    for(; i < DISPLAY_ARRAY_SIZE * 6; i ++){
        displayArray[i] = 0;
    }
    arrayCharIndex = 0;
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
    }
}

void writeToLED(){
    scrollIndex = 0;
    while(1){
        
    }
}

void ledMapping(uint8_t scrollIndex){
    uint8_t index = 0;
    for(; index < LEV_NUM; index++){
        uint8_t thisRow = displayArray[index + scrollIndex];
        writeToArray(thisRow, 2, index);
        writeToArray(thisRow, 3, index);
        writeToArray(thisRow, 4, index);
        writeToArray(thisRow, 5, index);
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
    for(; j < DISPLAY_ARRAY_SIZE * 6; j++){
        sprintf(buffer, "%d\r\n", displayArray[j]);
//        sprintf(buffer, "test\r\n");
        uart_write_string(buffer);
    }
}