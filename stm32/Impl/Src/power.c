#include "power.h"
#include "gpio.h"
#include "tim.h"
#include <appState.h>
#include "adc.h"
#include <bridge.h>

uint32_t findZeroTicks;

uint8_t deadTimeFlag = 0;
uint32_t deadTimeTicks = 0;
uint32_t motorBeepTicks = 0;

static void handleFindZero(void);

void FindZero(void) {
	state.currentAction = FIND_ZERO;
	findZeroTicks = 0;
	TurnOnLeft();
}

void updateCurrent() {
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint32_t ADC_raw = HAL_ADC_GetValue(&hadc1);
	state.motor1current = ADC_raw;

	handleFindZero();

	if (state.currentAction == FIND_POS) {
		if (state.position.motor1pos < state.motor1targetpos) {
			TurnOnRight();
		} else if (state.position.motor1pos > state.motor1targetpos) {
			TurnOnLeft();
		} else {
			motorStop();
		}
	}
}

void SetHighSpeed(void)
{
	state.position.motor1speed = HIGH_SPEED;
	state.position.pwmWidth = 200;
}
void SetMiddleSpeed(void)
{
	state.position.motor1speed = MIDDLE_SPEED;
	state.position.pwmWidth = 100;
}
void SetLowSpeed(void)
{
	state.position.motor1speed = LOW_SPEED;
	state.position.pwmWidth = 20;
}


void handleMotorBeep() {
	if (state.motorBeepFlag && !deadTimeFlag) {
		motorBeepTicks++;
		if (state.motorDirection == LEFT) {
			TurnOnRight();
		} else {
			TurnOnLeft();
		}
		if (motorBeepTicks == 50) {
			motorStop();
			motorBeepTicks = 0;
			state.motorBeepFlag = 0;
		}
	}
}

void handleFindZero() {
	if (state.currentAction != IDLE) {
		if (state.motor1current < 10 && findZeroTicks <= 100) {
			findZeroTicks++;
		}
		if (state.motor1current < 10 && findZeroTicks > 100
				&& state.motorDirection == LEFT) {
			findZeroTicks = 0;
			state.position.motor1pos = 0;
			state.currentAction = IDLE;
			motorStop();
			state.motorBeepFlag = 1;
		}
		if (state.motor1current < 10 && findZeroTicks > 100
				&& state.motorDirection == RIGHT) {
			findZeroTicks = 0;
			state.position.motor1maxpos = state.position.motor1pos;
			state.currentAction = IDLE;
			motorStop();
			state.motorBeepFlag = 1;
		}
	}

}

void updateBridgeState() {
	if (deadTimeFlag && deadTimeTicks < 10) {
		deadTimeTicks++;
	}

	if (deadTimeFlag && deadTimeTicks >= 10) {
		deadTimeFlag = 0;
		deadTimeTicks = 0;
		if (state.motorDirection == LEFT) {
			bridgeLeft();
		} else if (state.motorDirection == RIGHT) {
			bridgeRight();
		} else {
			state.currentAction = IDLE;
			bridgeOff();
		}
	}
}

void goToPos(int16_t pos) {
	state.currentAction = FIND_POS;
	state.motor1targetpos = pos;
}

void deadTimeStart() {
	deadTimeFlag = 1;
	deadTimeTicks = 0;
	bridgeOff();
}

void TurnOnLeft(void) {
	if (state.motorDirection != LEFT) {
		state.motorDirection = LEFT;
		deadTimeStart();
	}
}

void TurnOnRight(void) {
	if (state.motorDirection != RIGHT) {
		state.motorDirection = RIGHT;
		deadTimeStart();
	}
}

void motorStop(void) {
	state.rotationPeriod = 0;
	state.motorDirection = NONE;
	state.currentAction = IDLE;
	bridgeOff();
}

