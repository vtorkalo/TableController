#include <app.h>
#include <power.h>
#include <appState.h>
#include "tim.h"
#include <encoder.h>
#include <powerMonitor.h>
#include <buttons.h>

uint8_t flag = 0;

uint8_t readbyte = 0;
uint32_t startDelayTicks = 0;
void appInit(void) {
	initAppState();
	initEncoder();

	HAL_TIM_Base_Start_IT(&htim2);
}

void timer(void) {

	if (startDelayTicks < 300) //wait for buttons capacitors charge.
	{
		startDelayTicks++;
		return;
	}

	updateCurrent();
	updatePowerMonitor();

	readEncoder();
	updateButtons();
}

void mainLoop(void) {
	if (saveStateFlag == 1) {
		saveStateFlag = 0;
		SaveState();
	}
}
