#include <powerMonitor.h>
#include <gpio.h>
#include <appState.h>
#include <power.h>

void updatePowerMonitor(void) {
	if (HAL_GPIO_ReadPin(POWER_FAILURE_GPIO_Port, POWER_FAILURE_Pin)
			== GPIO_PIN_RESET && state.powerFailureFlag == 0) {
		motorStop();
		saveStateFlag = 1;
		state.powerFailureFlag = 1;
	}

	if (HAL_GPIO_ReadPin(POWER_FAILURE_GPIO_Port, POWER_FAILURE_Pin)
			== GPIO_PIN_SET && state.powerFailureFlag == 1) {
		state.powerFailureFlag = 0;
		//LoadState();
	}
}
