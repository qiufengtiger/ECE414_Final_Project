#include "lettters_display.h"

void decode(char c, uint8_t charNum){
    uint8_t line = charNum * 6;
    switch(c){
        case 'A':
            //line4 ooxxx
            //line3 oxoxo
            //line2 xooxo
            //line1 oxoxo
            //line0 ooxxx
            displayArray[line] = 0b00111;
            displayArray[++line] = 0b01010;
            displayArray[++line] = 0b10010;
            displayArray[++line] = 0b01010;
            displayArray[++line] = 0b00111;
            displayArray[++line] = 0b00000;//space
            break;
        case 'B':
            displayArray[line] = 0b01010;
            displayArray[++line] = 0b10101;
            displayArray[++line] = 0b10101;
            displayArray[++line] = 0b10101;
            displayArray[++line] = 0b11111;
            displayArray[++line] = 0b00000;
            break;
    }
}

void testDecode(){
    char test[] = "ABABAB";
    int i = 0;
    uint8_t buffer[64];
    
    uart_init();
//    while(1){
//        char c = test[i];
//        decode(c, i);
//        i++;    
//    }
//    int j = 0;
//    for(; j < 32; j++){
//        sprintf(buffer, "%d\r\n", displayArray[j]);
        sprintf(buffer, "test\r\n");
        uart_write_string(buffer);
//    }
}