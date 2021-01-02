#include <encoder.h>
#include "gpio.h"
#include "appState.h"

GPIO_PinState motor1_prev_state;
GPIO_PinState motor1_initial_state;

void initEncoder()
{
	motor1_initial_state = HAL_GPIO_ReadPin(MOTOR1_ENCODER_GPIO_Port, MOTOR1_ENCODER_Pin);
	motor1_prev_state = motor1_initial_state;
}

void readEncoder(void)
{
	GPIO_PinState motor1currentState = HAL_GPIO_ReadPin(MOTOR1_ENCODER_GPIO_Port, MOTOR1_ENCODER_Pin);
	if (motor1currentState != motor1_prev_state && motor1currentState == motor1_initial_state)
	{
		if (state.motorDirection == LEFT)
		{
		    state.position.motor1pos--;
		}
		else if (state.motorDirection == RIGHT)
		{
			state.position.motor1pos++;
		}
	}
	motor1_prev_state = motor1currentState;
}
