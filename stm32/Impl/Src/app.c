#include <app.h>
#include <power.h>
#include <appState.h>
#include "tim.h"
#include <encoder.h>
#include <powerMonitor.h>
#include <buttons.h>

uint8_t flag = 0;

uint8_t readbyte = 0;
void appInit(void) {
	initAppState();
	initEncoder();


	HAL_TIM_Base_Start_IT(&htim2);
}

void timer(void) {
	updateCurrent();
	readEncoder();
	updateButtons();
	updatePowerMonitor();
}

void mainLoop(void) {
	if (saveStateFlag == 1) {
		saveStateFlag = 0;
		SaveState();
	}
}
