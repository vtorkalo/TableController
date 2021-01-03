#include <bridge.h>
#include <tim.h>
#include <gpio.h>
#include <appState.h>
#include <stdint.h>

static void setPwmWidth(uint8_t width);

void bridgeLeft() {
	updatePwmWidth();
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3); //LEFT HIGH
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_4); //RIGHT HIGH

	HAL_GPIO_WritePin(BRIDGE1_LEFT_LOW_GPIO_Port, BRIDGE1_LEFT_LOW_Pin,
			GPIO_PIN_SET);
	HAL_GPIO_WritePin(BRIDGE1_RIGHT_LOW_GPIO_Port, BRIDGE1_RIGHT_LOW_Pin,
			GPIO_PIN_RESET);
}

uint32_t pwmUpdateCounter = 0;

void updatePwmWidth() {
	if (state.motorDirection == NONE) {
		return;

	}
	int16_t expectedPeriod;
	switch (state.position.motor1speed) {
	case LOW_SPEED:
		expectedPeriod = 160;
		break;
	case HIGH_SPEED:
		setPwmWidth(128);
		expectedPeriod = 70;
		return;
	}

	if (state.rotationPeriod - expectedPeriod > 10 && state.pwmWidth < 128) {
		state.pwmWidth++;
	} else if (expectedPeriod - state.rotationPeriod > 10 && state.pwmWidth > 20) {
		state.pwmWidth--;
	}

	setPwmWidth(state.pwmWidth);
}

void setPwmWidth(uint8_t width) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, width);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, width);
}

void bridgeRight() {
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_3); //LEFT HIGH
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4); // RIGHT HIGH

	HAL_GPIO_WritePin(BRIDGE1_LEFT_LOW_GPIO_Port, BRIDGE1_LEFT_LOW_Pin,
			GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BRIDGE1_RIGHT_LOW_GPIO_Port, BRIDGE1_RIGHT_LOW_Pin,
			GPIO_PIN_SET);
}

void bridgeOff(void) {
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_4);

	HAL_GPIO_WritePin(BRIDGE1_LEFT_LOW_GPIO_Port, BRIDGE1_LEFT_LOW_Pin,
			GPIO_PIN_SET);
	HAL_GPIO_WritePin(BRIDGE1_RIGHT_LOW_GPIO_Port, BRIDGE1_RIGHT_LOW_Pin,
			GPIO_PIN_SET);
}
