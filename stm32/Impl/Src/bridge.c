#include <bridge.h>
#include <tim.h>
#include <gpio.h>
#include <appState.h>
#include <stdint.h>

void bridgeLeft() {
	setPwmWidth();
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3); //LEFT HIGH
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_4); //RIGHT HIGH

	HAL_GPIO_WritePin(BRIDGE1_LEFT_LOW_GPIO_Port, BRIDGE1_LEFT_LOW_Pin,
			GPIO_PIN_SET);
	HAL_GPIO_WritePin(BRIDGE1_RIGHT_LOW_GPIO_Port, BRIDGE1_RIGHT_LOW_Pin,
			GPIO_PIN_RESET);
}

void setPwmWidth() {
	uint8_t pwmWidth;
	switch (state.position.motor1speed) {
	case LOW_SPEED:
		pwmWidth = 40;
		break;
	case HIGH_SPEED:
		pwmWidth = 128;
		break;
	}
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwmWidth);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwmWidth);
}

void bridgeRight() {
	setPwmWidth();
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
