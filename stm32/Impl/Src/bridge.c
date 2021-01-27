#include <bridge.h>
#include <tim.h>
#include <gpio.h>
#include <appState.h>
#include <stdint.h>

static void setPwmWidth(uint8_t width);
static float calculatePID(int32_t error);

void bridgeLeft() {
	updatePwmWidth();
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3); //LEFT HIGH
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_4); //RIGHT HIGH

	HAL_GPIO_WritePin(BRIDGE1_LEFT_LOW_GPIO_Port, BRIDGE1_LEFT_LOW_Pin,
			GPIO_PIN_SET);
	HAL_GPIO_WritePin(BRIDGE1_RIGHT_LOW_GPIO_Port, BRIDGE1_RIGHT_LOW_Pin,
			GPIO_PIN_RESET);
}

int16_t prevError = 0;
float integralPrev = 0;
const uint16_t PWM_MAX = 255;
const uint16_t PWM_MIN = 6;

const float Kp = 0.8;
const float Kd = 0.08;
const float Ki = 0.01;

void updatePwmWidth(void) {
	if (state.motorDirection == NONE) {
		return;
	}
	int16_t expectedPeriod;
	switch (state.position.motor1speed) {
	case LOW_SPEED:
		expectedPeriod = 160;
		break;
	case MIDDLE_SPEED:
		expectedPeriod = 80;
		break;
	case HIGH_SPEED:
		expectedPeriod = 80;
		state.position.pwmWidth = PWM_MAX;
		setPwmWidth(PWM_MAX);
		return;
	}

	if (state.rotationPeriod > 0 && state.currentAction > 0) {
		int32_t error = state.rotationPeriod - expectedPeriod;
		state.position.pwmWidth = calculatePID(error);
		prevError = error;
	}
	else
	{
		prevError = 0;
		integralPrev = 0;
	}
	if (state.position.pwmWidth >= PWM_MIN
			&& state.position.pwmWidth <= PWM_MAX) {
		setPwmWidth((uint8_t) state.position.pwmWidth);
	}
}

float calculatePID(int32_t error) {
	float integralCor = integralPrev + Ki * error;
	integralPrev = integralCor;

	float correction = 0;
	correction += integralCor;
	correction += Kp * error;
	correction += Kd * (error - prevError);

	float newPwm = state.position.pwmWidth + correction / 10;

	if (newPwm < PWM_MIN) {
		newPwm = PWM_MIN;
	} else if (newPwm > PWM_MAX) {
		newPwm = PWM_MAX;
	}

	return newPwm;
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
