#include "TouchScreenDisplay.h"

volatile uint8_t gameover;
void __ISR(0, ipl1auto) InterruptHandler(void){
    gameover = 1;
    mINT4ClearIntFlag();
}

uint16_t touchMappingX(uint16_t y){
    double temp = (y - 960)*(-0.372);
    return (int)temp;
}

//y cood mapping
uint16_t touchMappingY(uint16_t x){
    double temp = (x - 140)*(0.324); 
    return (int)temp;
}

void touchScreenParamInit(){
	// Turn off analog function of Ports A and B
    ANSELA = 0; 
    ANSELB = 0; 
    
    // Turn off comparator functions
    CM1CON = 0; 
    CM2CON = 0;

    // TRISB = (TRISB | 0x0001); 
    // TRISB = (TRISB | 0x300); //RB8 & RB9 for joystick
    // TRISB = (TRISB | 0x300); // up & down buttons
    // TRISB = (TRISB & 0x7BCF); // output code
    // TRISA = (TRISA & 0xB);
    TRISB = TRISB & 0xCFF;

    // Initialize display
    tft_init_hw();
    tft_begin();
    tft_setRotation(3);
    tft_setTextColor(BLACK);  
    tft_setTextSize(2);
    tft_fillScreen(BLACK);
    tft_fillRect(81, 0, 240, 240, WHITE);
    //initialize touch screen
    SYSTEMConfigPerformance(PBCLK);
    configureADC();

    gameover = 0;
    INT4R = 0x4; //RPB7, pin 16
    mINT4SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
    mINT4IntEnable(1);

    joystickDirY = DEFAULT;
    joystickDirX = DEFAULT;
    upButtonState = 0;
    downButtonState = 0;
    buttonPressed = DEFAULT;
    outputDir = DEFAULT;
    outputDirLock = 0;
    levelToPulse = 0;

    tabMsgColor = GRAY;
    tabSnakeColor = GRAY;
    tabRobotColor = GRAY;
    tabModelColor = GRAY;
    tabSelected = 1;
    tabLevelToPulse = 0;
    selectTab(tabSelected);

    T1CON = 0x8030;
    TMR1 = 0;
}

void TabsRefresh(){
	uint8_t buffer[64];
	tft_fillRect(0, 0, 80, 60, tabMsgColor);
	tft_fillRect(0, 60, 80, 60, tabSnakeColor);
	tft_fillRect(0, 120, 80, 60, tabRobotColor);
	tft_fillRect(0, 180, 80, 60, tabModelColor);
	tft_drawRect(0, 0, 80, 60, WHITE);
	tft_drawRect(0, 60, 80, 60, WHITE);
	tft_drawRect(0, 120, 80, 60, WHITE);
	tft_drawRect(0, 180, 80, 60, WHITE);
	tft_setCursor(25, 15);
	sprintf(buffer, "Msg");
	tft_writeString(buffer);
	tft_setCursor(13, 75);
	sprintf(buffer, "Snake");
	tft_writeString(buffer); 
	tft_setCursor(13, 135);
	sprintf(buffer, "Robot");
	tft_writeString(buffer); 
	tft_setCursor(13, 195);
	sprintf(buffer, "Model");
	tft_writeString(buffer); 	
}

void selectTab(uint8_t index){
	tft_fillRect(81, 0, 240, 240, WHITE);
	switch(index){
		case 1:
			tabMsgColor = WHITE;
			tabSnakeColor = GRAY;
			tabRobotColor = GRAY;
			tabModelColor = GRAY;
			runMsgContent();
			sendToMainControl(1);
			break;
		case 2:
			tabMsgColor = GRAY;
			tabSnakeColor = WHITE;
			tabRobotColor = GRAY;
			tabModelColor = GRAY;
			runSnakeContent();
			sendToMainControl(2);
			break;
		case 3:
			tabMsgColor = GRAY;
			tabSnakeColor = GRAY;
			tabRobotColor = WHITE;
			tabModelColor = GRAY;
			runRobotContent();
			sendToMainControl(3);
			break;
		case 4:
			tabMsgColor = GRAY;
			tabSnakeColor = GRAY;
			tabRobotColor = GRAY;
			tabModelColor = WHITE;
			runModelContent();
			sendToMainControl(4);
			break;
		default:
			break;
	}
	TabsRefresh();
}

uint8_t detectTouch(){
	struct TSPoint p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    getPoint(&p);
    uint16_t oldX = p.x;
    uint16_t oldY = p.y;     
    p.y = touchMappingY(oldX);
    p.x = touchMappingX(oldY);
    if(p.z > 300){
    	if(p.x > 0 && p.x < 80){
    		if(p.y > 5 && p.y < 55){
    			// selectTab(1);
    			return 1;
    		}
    		else if(p.y > 60 && p.y < 120){
    			return 2;
    		}
    		else if(p.y > 120 && p.y < 180){
    			return 3;
    		}
    		else if(p.y > 180 && p.y < 240)
    			return 4;
    	}
    	// if(p.x > 160 && p.x < 240 && p.y > 120 && p.y < 180){
    	// 	return 5;
    	// }
    	// TabsRefresh();
    }
    else{
    	tabLevelToPulse = 0;
    }
    return 0;
}

void runButtons(uint8_t button) {
	if (button == 0) {

	} 
	else if(button == 1 && tabSelected != 1){
		gameover = 0;
		tabSelected = 1;
		selectTab(tabSelected);
		// TabsRefresh();
	} 
	else if(button == 2 && tabSelected != 2){
		gameover = 0;
		tabSelected = 2;
		selectTab(tabSelected);
		// TabsRefresh();
	}
	else if(button == 3 && tabSelected != 3){
		gameover = 0;
		tabSelected = 3;
		selectTab(tabSelected);
		// TabsRefresh();
	}
	else if(button == 4 && tabSelected != 4){
		gameover = 0;
		tabSelected = 4;
		selectTab(tabSelected);
		// TabsRefresh();
	}
	// else if(button == 5){
	// 	gameover = 0;
	// 	selectTab(tabSelected);
	// 	sendToMainControl(NOT_AVAILABLE, 1, 0);
	// 	// TabsRefresh();
	// }
}

void runMsgContent(){
	uint8_t buffer[64];
	tft_setCursor(90, 112);
	sprintf(buffer, "Running Msg Display");
	tft_writeString(buffer);
}

void runSnakeContent(){
	uint8_t buffer[64];
	tft_setCursor(90, 112);
	sprintf(buffer, "Running Snake Game");
	tft_writeString(buffer);
}

void runRobotContent(){
	uint8_t buffer[64];
	tft_setCursor(90, 112);
	sprintf(buffer, "Running Robot Game");
	tft_writeString(buffer);
}

void runModelContent(){
	uint8_t buffer[64];
	tft_setCursor(90, 112);
	sprintf(buffer, "Running Model Disp");
	tft_writeString(buffer);
}

void checkGameover(){
	uint8_t buffer[64];
	if(gameover && (tabSelected == 2 | tabSelected == 3)){
		tft_fillRect(110, 20, 210, 15, WHITE); //refresh
		tft_setCursor(150, 20);
		sprintf(buffer, "Gameover");
		tft_writeString(buffer);
		tft_fillRect(110, 50, 210, 15, WHITE);
		tft_setCursor(110, 50);
		sprintf(buffer, "Rst => restart");
		tft_writeString(buffer);
		tft_fillRect(110, 80, 210, 15, WHITE);
	}
}

// void checkDir(){
// 	if(!gameover){
// 		checkJoystickDir();
// 		checkButtonsDir();	
// 	}
// 	if(outputDirLock == 0){
// 		levelToPulse = 0;
// 	}
// 	else if(outputDirLock == 1 && levelToPulse == 0){
// 		sendToMainControl(outputDir, 0, 0);
// 		outputDir = DEFAULT;
// 		outputDirLock = 0;
// 		levelToPulse = 1;
// 	}
// }

// void checkJoystickDir(){
// 	uint8_t buffer[64];
// 	uint8_t inputDirY = NOT_AVAILABLE;
// 	uint8_t inputDirX = NOT_AVAILABLE;
// 	uint16_t inputY = analog_in_read(5); //AN5, PIN7
// 	uint16_t inputX = analog_in_read(11); //AN11, PIN24
// 	if(inputY > 700)
// 		inputDirY = FORWARD;
// 	else if(inputY < 340)
// 		inputDirY = BACKWARD;
// 	else
// 		inputDirY = NOT_AVAILABLE;

// 	if(inputX > 700)
// 		inputDirX = RIGHT;
// 	else if(inputX < 340)
// 		inputDirX = LEFT;
// 	else
// 		inputDirX = NOT_AVAILABLE;
// 	if(/*!gameover && (*/tabSelected == 2 | tabSelected == 3/*)*/){
// 		// if(inputDirY != joystickDirY)
// 		// {
// 			// joystickDirY = inputDirY;
// 			tft_fillRect(110, 20, 210, 15, WHITE);
// 			tft_setCursor(110, 20);
// 			if(inputDirY == FORWARD)
// 				sprintf(buffer, "Y axis: FORWARD");
// 			else if(inputDirY == BACKWARD)
// 				sprintf(buffer, "Y axis: BACKWARD");
// 			else
// 				sprintf(buffer, "Y axis: N/A");
// 			tft_writeString(buffer);
// 			if(outputDirLock == 0 && inputDirY != NOT_AVAILABLE){
// 				outputDir = inputDirY;
// 				outputDirLock = 1;
// 			}
// 		// }	
// 		// if(inputDirX != joystickDirX)
// 		// {
// 			// joystickDirX = inputDirX;
// 			tft_fillRect(110, 50, 210, 15, WHITE);
// 			tft_setCursor(110, 50);
// 			if(inputDirX == RIGHT)
// 				sprintf(buffer, "X axis: RIGHT");
// 			else if(inputDirX == LEFT)
// 				sprintf(buffer, "X axis: LEFT");
// 			else
// 				sprintf(buffer, "X axis: N/A");
// 			tft_writeString(buffer);
// 			if(outputDirLock == 0 && inputDirX != NOT_AVAILABLE){
// 				outputDir = inputDirX;
// 				outputDirLock = 1;
// 			}
// 		// }	
// 	}
// }

// void checkButtonsDir(){
// 	uint8_t buffer[64];
// 	uint16_t upInput = !!(PORTB & 0x200);
// 	uint16_t downInput = !!(PORTB & 0x100);
// 	if(upInput == 1)
// 		buttonPressed = UP;
// 	else if(downInput == 1)
// 		buttonPressed = DOWN;
// 	else
// 		buttonPressed = NOT_AVAILABLE;
// 	// if(upInput != upButtonState && buttonPressed == DEFAULT &&  (tabSelected == 2 | tabSelected == 3)){
// 	// 	buttonPressed = UP;
// 	// 	TMR1 = 0;
// 	// }
// 	// else if(downInput != downButtonState && buttonPressed == DEFAULT &&  (tabSelected == 2 | tabSelected == 3)){
// 	// 	buttonPressed = DOWN;
// 	// 	TMR1 = 0;
// 	// }
// 	if(/*TMR1 > 5000*//*!gameover && (*/tabSelected == 2 | tabSelected == 3/*)*/){
// 		tft_fillRect(110, 80, 210, 15, WHITE);
// 		tft_setCursor(110, 80);
// 		if(buttonPressed == UP){
// 			sprintf(buffer, "Z axis: UP");
// 			upButtonState = 1;
// 		}
// 		else if(buttonPressed == DOWN){
// 			sprintf(buffer, "Z axis: DOWN");
// 			downButtonState = 1;
// 		}
// 		else{
// 			sprintf(buffer, "Z axis: N/A");
// 			upButtonState = 0;
// 			downButtonState = 0;
// 		}
// 		tft_writeString(buffer);
// 	}
// 	if(outputDirLock == 0 && buttonPressed != NOT_AVAILABLE){
// 		outputDir = buttonPressed;
// 		outputDirLock = 1;
// 	}
// }


/**
 * output: 5 bit code
 * 00000: default
 * 00001: FORWARD
 * 00010: BACKWARD
 * 00011: LEFT
 * 00100: RIGHT
 * 00101: UP
 * 00110: DOWN
 * 01000: RESTART
 * 01001: Msg (TAB 1)
 * 01010: Snake (TAB 2)
 * 01011: Robot (TAB 3)
 * 01100: Model (TAB 4)
 */
void sendToMainControl(uint8_t tabSelected){
	uint8_t outputCode = 0;
	uint16_t portbOut = 0;
	if(tabSelected == 1){
		// outputCode = 0b00;
		outputCode = 0b11; //inverter
	}
	else if(tabSelected == 2){
		// outputCode = 0b01;
		outputCode = 0b10;
	}
	else if(tabSelected == 3){
		// outputCode = 0b10;
		outputCode = 0b01;
	}
	else if(tabSelected == 4){
		// outputCode = 0b11;
		outputCode = 0b00;
	}
	portbOut += (!!(outputCode & 0b10));
	portbOut <<= 1;
	portbOut += (!!(outputCode & 0b01));
	portbOut <<= 8;
	PORTB = (PORTB & 0b0011111111) | portbOut;
}

void runTouchScreenDisplayTests(){
	uint8_t buttonIndex = 0;
	touchScreenParamInit();
	// TabsRefresh();
	while(1){
		// checkGameover();
		// checkJoystickDir();
		// checkButtonsDir();
		// checkDir();
		buttonIndex = detectTouch();
		runButtons(buttonIndex);
		buttonIndex = 0;
	}
}