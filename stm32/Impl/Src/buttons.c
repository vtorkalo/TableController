#include <buttons.h>
#include <stdbool.h>
#include <gpio.h>
#include <power.h>
#include <appState.h>

uint8_t buttonPrevState[5] = { 0 };
uint8_t buttonState[5] = { 0 };
uint32_t buttonTicks[5] = { 0 };

static void buttonDown(uint8_t button);
static void buttonUp(uint8_t button);
static void buttonLongDown(uint8_t button);
static void buttonUpAfterLongPress(uint8_t button);
const uint32_t LONG_PRESS_TICKS = 2000;

void updateButtons() {
	buttonState[0] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin)
			== GPIO_PIN_RESET;
	buttonState[1] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin)
			== GPIO_PIN_RESET;
	buttonState[2] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin)
			== GPIO_PIN_RESET;
	buttonState[3] = HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin)
			== GPIO_PIN_RESET;
	buttonState[4] = HAL_GPIO_ReadPin(BUTTON5_GPIO_Port, BUTTON5_Pin)
			== GPIO_PIN_RESET;

	for (uint8_t i = 0; i < sizeof(buttonState); i++) {
		if (buttonState[i] && !buttonPrevState[i]) {
			buttonTicks[i] = 0;
			buttonDown(i);
		}
		if (!buttonState[i] && buttonPrevState[i]) {
			if (buttonTicks[i] < LONG_PRESS_TICKS) {
				buttonUp(i);
			} else {
				buttonUpAfterLongPress(i);
				buttonTicks[i] = 0;
			}
		}

		if (buttonState[i] && buttonPrevState[i]
				&& buttonTicks[i] <= LONG_PRESS_TICKS) {
			buttonTicks[i]++;
		}
		if (buttonState[i] && buttonPrevState[i]
				&& buttonTicks[i] == LONG_PRESS_TICKS) {
			buttonLongDown(i);
		}

		buttonPrevState[i] = buttonState[i];
	}
}

uint8_t stopFlag = 0;

void buttonDown(uint8_t button) {
	if (button == 0 && state.currentAction == IDLE) {
		state.currentAction = MOVE_LEFT;
		TurnOnLeft();
		return;
	}
	if (button == 1 && state.currentAction == IDLE) {
		state.currentAction = MOVE_RIGHT;
		TurnOnRight();
		return;
	}
	if (state.currentAction != IDLE) {
		stopFlag = true;
		motorStop();
		return;
	}
}

void buttonUp(uint8_t button) {
	if (button == 0 || button == 1) {
		motorStop();
		return;
	}
	if (stopFlag) {
		stopFlag = false;
		return;
	}
	if (button == 2) {
		goToPos(state.position.motor1memory1);
		return;
	}
	if (button == 3) {
		goToPos(state.position.motor1memory2);
		return;
	}
	if (button == 4) {
		goToPos(state.position.motor1memory3);
		return;
	}

}

void buttonLongDown(uint8_t button) {
	if (buttonState[0] && buttonState[1] && button == 1) {
		state.position.motor1speed = state.position.motor1speed == LOW_SPEED ? HIGH_SPEED : LOW_SPEED;
		state.motorBeepFlag = 1;
		return;
	}
	if (button == 2) {
		state.position.motor1memory1 = state.position.motor1pos;
		state.motorBeepFlag = 1;
		return;
	}
	if (button == 3) {
		state.position.motor1memory2 = state.position.motor1pos;
		state.motorBeepFlag = 1;
		return;
	}
	if (button == 4) {
		state.position.motor1memory3 = state.position.motor1pos;
		state.motorBeepFlag = 1;
		return;
	}
}

void buttonUpAfterLongPress(uint8_t button) {
	if (button == 0 || button == 1) {
			motorStop();
		return;
	}

}
