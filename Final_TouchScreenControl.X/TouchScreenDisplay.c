#include "TouchScreenDisplay.h"

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

    tabMsgColor = GRAY;
    tabSnakeColor = GRAY;
    tabRobotColor = GRAY;
    tabModelColor = GRAY;
    tabSelected = 1;
    selectTab(tabSelected);
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
	switch(index){
		case 1:
			tabMsgColor = WHITE;
			tabSnakeColor = GRAY;
			tabRobotColor = GRAY;
			tabModelColor = GRAY;
			runMsgContent();
			break;
		case 2:
			tabMsgColor = GRAY;
			tabSnakeColor = WHITE;
			tabRobotColor = GRAY;
			tabModelColor = GRAY;
			runSnakeContent();
			break;
		case 3:
			tabMsgColor = GRAY;
			tabSnakeColor = GRAY;
			tabRobotColor = WHITE;
			tabModelColor = GRAY;
			runRobotContent();
			break;
		case 4:
			tabMsgColor = GRAY;
			tabSnakeColor = GRAY;
			tabRobotColor = GRAY;
			tabModelColor = WHITE;
			runModelContent();
			break;
		default:
			break;
	}
	TabsRefresh();
}

void runMsgContent(){
	uint8_t buffer[64];
	tft_setCursor(90, 112);
	sprintf(buffer, "Running Msg Display");
	tft_writeString(buffer);
}

void runSnakeContent(){

}

void runRobotContent(){

}

void runModelContent(){

}

void runTouchScreenDisplayTests(){
	touchScreenParamInit();
	TabsRefresh();
}
	