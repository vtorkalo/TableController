#include <encoder.h>
#include "gpio.h"
#include "appState.h"
#include "periodCircleBuffer.h"

GPIO_PinState motor1_prev_state;
GPIO_PinState motor1_initial_state;

uint32_t rotationPeriod = 999;

void initEncoder() {
	motor1_initial_state = HAL_GPIO_ReadPin(MOTOR1_ENCODER_GPIO_Port,
	MOTOR1_ENCODER_Pin);
	motor1_prev_state = motor1_initial_state;
}

void readEncoder(void) {
	if (state.motor1current < 10)
	{
		return;
	}
	rotationPeriod++;
	if (state.motorDirection == NONE) {
		rotationPeriod = 0;
	}
	GPIO_PinState motor1currentState = HAL_GPIO_ReadPin(
	MOTOR1_ENCODER_GPIO_Port, MOTOR1_ENCODER_Pin);
	if (motor1currentState != motor1_prev_state
			&& motor1currentState == motor1_initial_state) {
		if (rotationPeriod > 0) {
			StoreMeasurment(rotationPeriod);
			rotationPeriod = 0;
		}

		if (state.motorDirection == LEFT) {
			state.position.motor1pos--;
		} else if (state.motorDirection == RIGHT) {
			state.position.motor1pos++;
		}
	}

	if (rotationPeriod > 0) {
		UpdateLast(rotationPeriod);
	}

	if (GetRecordsCount() == CIRCLE_BUFFER_SIZE) {
		uint32_t sum = 0;
		for (uint8_t i = 0; i < CIRCLE_BUFFER_SIZE; i++) {
			sum += (CIRCLE_BUFFER_SIZE - i)
					* GetMeasurement(CIRCLE_BUFFER_SIZE - i - 1);
		}

		state.rotationPeriod = ((float) 2
				/ ((float) (CIRCLE_BUFFER_SIZE * (CIRCLE_BUFFER_SIZE + 1))))
				* sum;
	}



	motor1_prev_state = motor1currentState;
}
