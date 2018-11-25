#include "robot.h"

void robotInit(){
	//initialize timer for random number
	T1CON = 0x8010;
	TMR1 = 0;
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
	setRobotGameArray(PLAYER, LEV_NUM / 2, ROW_NUM / 2, COL_NUM / 2); //initialize player pos to the center
}

void generateEnemies(){
	
}
