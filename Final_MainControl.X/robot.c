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
				setRobotGameArray(EMPTY, i, j, k);
			}
		}
	}			
	//initialize player pos to the center
	player.lev = LEV_NUM / 2;
	player.row = ROW_NUM / 2;
	player.col = COL_NUM / 2;
	player.type = PLAYER;
	setRobotGameArray(PLAYER, player.lev, player.row, player.col);
	mT1SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
    mT1IntEnable(1);
    timer_ms_count = 0;
    playerIsOn = 1;
}

void playerMove(uint8_t dir){
	if(!isBorder(player.lev, player.row, player.col, dir) && !isEnemy(player.lev, player.row, player.col, dir)){
		setRobotGameArray(EMPTY, player.lev, player.row, player.col);
		switch(dir){
		case 2: 
			player.row -= 1;
			break;
		case 8:
			player.row += 1;
			break;
		case 4:
			player.col += 1;
			break;
		case 6:
			player.col -= 1;
			break;
		case 1:
			player.lev -= 1;
			break;
		case 7:
			player.lev += 1;
			break;
		default:
			return;
		}
		setRobotGameArray(PLAYER, player.lev, player.row, player.col);
	}
}

uint8_t enemiesMove(){
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t k = 0;
	uint8_t newEnemyLev = 0;
	uint8_t newEnemyRow = 0;
	uint8_t newEnemyCol = 0;
	uint8_t levDistance = 0;
	uint8_t rowDistance = 0;
	uint8_t colDistance = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				if(getRobotGameArray(i, j, k) == ENEMY){
					newEnemyLev = i;
					newEnemyRow = j;
					newEnemyCol = k;
					levDistance = absolute(i - newEnemyLev);
					rowDistance = absolute(j - newEnemyRow);
					colDistance = absolute(k - newEnemyCol);
					setRobotGameArray(EMPTY, i, j, k);
					if(levDistance >= rowDistance && levDistance >= colDistance){
						if(player.lev > i) newEnemyLev++;
						else if(player.lev < i) newEnemyLev--;
					}
					else if(rowDistance >= levDistance && rowDistance >= colDistance){
						if(player.row > j) newEnemyRow++;
						else if(player.row < j) newEnemyRow--;
					}
					else{
						if(player.col > k) newEnemyCol++;
						else if(player.col < k) newEnemyCol--;
					}
					if(player.lev == newEnemyLev && player.row == newEnemyRow && player.col == newEnemyCol){
						return 1; //gameover
					}
					else{
						setRobotGameArray(ENEMY, newEnemyLev, newEnemyRow, newEnemyCol);
					}
				}
				
			}
		}
	}
	return 0;
}

uint8_t isEnemy(uint8_t levIndex, uint8_t rowIndex, uint8_t colIndex, uint8_t dir){
	uint8_t targetLev = player.lev;
	uint8_t targetRow = player.row;
	uint8_t targetCol = player.col;
	switch(dir){
		case 2: 
			targetRow -= 1;
			break;
		case 8:
			targetRow += 1;
			break;
		case 4:
			targetCol += 1;
			break;
		case 6:
			targetCol -= 1;
			break;
		case 1:
			targetLev -= 1;
			break;
		case 7:
			targetLev += 1;
			break;
	}
	if(getRobotGameArray(targetLev, targetRow, targetCol) == ENEMY)
		return 1;
	return 0;
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
			if(getRobotGameArray(enemyLev, enemyRow, enemyCol) != EMPTY)
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

void gameover(){
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < LEV_NUM; i++){
		for(j = 0; j < ROW_NUM; j++){
			for(k = 0; k < COL_NUM; k++){
				setRobotGameArray(PLAYER, i, j, k);
			}
		}
	}
}

void runRobotTests(){
	uint8_t changed = 0;
	uint8_t lose = 0;
	uart_init();
	robotInit();
	generateEnemies();
	robotSetLED();
	testPrintLedStatus();
	while(1){
		if(PLAYER_FLASH_ON && timer_ms_count == PLAYER_FLASH_MSEC){
			playerIsOn = !playerIsOn;
			changed = 1;	
		}
		char input = uart_read_nb();
		uint8_t dir = input - 48;
		if(dir > 0 && dir < 9 && dir != 3 && dir != 5 && lose == 0){
			// gameover();
			playerIsOn = 1;
			playerMove(dir);
			lose = enemiesMove();
			changed = 1;
		}
		if(changed){
			if(lose) gameover();
			robotSetLED();
			testPrintLedStatus();
			timer_ms_count = 0;
			changed = 0;
		}	
	}
}
