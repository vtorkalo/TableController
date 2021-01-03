#include <app.h>
#include <power.h>
#include <appState.h>
#include "tim.h"
#include <encoder.h>
#include <powerMonitor.h>
#include <buttons.h>

void appInit(void) {
	HAL_Delay(100);
	initAppState();
	initEncoder();

	HAL_TIM_Base_Start_IT(&htim2);
}

void timer(void) { // 100 Hz
	updateCurrent();
	updatePwmWidth();

	updatePowerMonitor();
}

void sysTick(void) //1000 Hz
{
	handleMotorBeep();
	updateBridgeState();
	readEncoder();
	updateButtons();
}

void mainLoop(void) {
	if (saveStateFlag == 1) {
		saveStateFlag = 0;
		SaveState();
	}
}
