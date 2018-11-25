#include "robot.h"

volatile uint32_t timer_ms_count;
void __ISR(0, ipl1auto) InterruptHandler(void){
    timer_ms_count++;
    mT1ClearIntFlag();
}

void robotInit(){
	//initialize timer for random number
	T1CON = 0x8010;
	T2CON = 0x8010;
	TMR1 = 0;
	TMR2 = 0;
	PR1 = 0x1000;
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setRobotGameArray(0, i, j, k);
			}
		}
	}			
	setRobotGameArray(PLAYER, LEV_NUM / 2, ROW_NUM / 2 , COL_NUM / 2); //initialize player pos to the center
	// player = {.lev = LEV_NUM / 2, .row = ROW_NUM / 2, .col = COL_NUM / 2, .type = PLAYER}; //store player pos
	mT1SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
    mT1IntEnable(1);
    timer_ms_count = 0;
    playerIsOn = 1;
}

void generateEnemies(){
	int i = 0;
	int isEmpty = 0;
	uint8_t enemyLev = 0;
	uint8_t enemyRow = 0;
	uint8_t enemyCol = 0;
	for(i = 0; i < NUMBER_OF_ENEMIES; i++){
		while(!isEmpty){
			enemyLev = TMR2 % LEV_NUM;
			enemyRow = (TMR2 >> 1) % ROW_NUM;
			enemyCol = (TMR2 >> 2) % COL_NUM;
			isEmpty = 1;
			if(getRobotGameArray(enemyLev, enemyRow, enemyCol) != 0)
				isEmpty = 0;
		}
		setRobotGameArray(ENEMY, enemyLev, enemyRow, enemyCol);
		isEmpty = 0;
	}
}

void robotSetLED(){
	int i = 0;
	int j = 0;
	int k = 0;
	uint8_t thisRow = 0;
	uint8_t type = 0;
	ledInit(); //clear cuboidArray first
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			thisRow = 0;
			for(k = COL_NUM; k > 0; k--){
				thisRow <<= 1;
				type = getRobotGameArray(i, j, k - 1); 
				if(!playerIsOn && type == PLAYER){
					type = 0;
				}
				thisRow += !!(type);			
			}
			setArray(thisRow, i, j);
		}
	}
}

void setRobotGameArray(uint8_t type, uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	robotGameArray[levIndex][rowIndex][colIndex] = type;
}

uint8_t getRobotGameArray(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex){
	return robotGameArray[levIndex][rowIndex][colIndex];
}

// char input = uart_read();
// 	uint8_t dir = input - 48;
// 	if(dir == 0){
// 		generateEnemies();
// 		robotSetLED();
// 		testPrintLedStatus();
// 	}

void runRobotTests(){
	uart_init();
	robotInit();
	generateEnemies();
	robotSetLED();
	testPrintLedStatus();
	while(1){
		if(timer_ms_count == FLASH_MSEC){
			playerIsOn = !playerIsOn;
			robotSetLED();
			testPrintLedStatus();
			timer_ms_count = 0;
		}		
	}
}
