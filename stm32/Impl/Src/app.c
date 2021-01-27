#include <app.h>
#include <power.h>
#include <appState.h>
#include "tim.h"
#include <encoder.h>
#include <powerMonitor.h>
#include <buttons.h>
#include <stdio.h>

void appInit(void) {
	HAL_Delay(100);
	initAppState();
	initEncoder();

	printf("Hello STM32 world!\r\n");

	HAL_TIM_Base_Start_IT(&htim2);
}

uint16_t timer100Hz = 0;
uint16_t timer10Hz = 0;

void timer(void) { // 100 Hz

}



void sysTick(void) //1000 Hz
{
	//handleMotorBeep();
	updateBridgeState();
	readEncoder();
	updateButtons();

	timer10Hz++;
	if (timer10Hz == 100)
	{
		timer10Hz = 0;
		updatePwmWidth();
	}

	timer100Hz++;
	if (timer100Hz == 10)
	{
		timer100Hz = 0;
		updateCurrent();
		updatePowerMonitor();
	}

}

void mainLoop(void) {
	if (saveStateFlag == 1) {
		saveStateFlag = 0;
		SaveState();
	}
}
