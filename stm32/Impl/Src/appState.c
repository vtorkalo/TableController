#include "appState.h"
#include <ee24.h>

void initAppState() {
	LoadState();
}

uint32_t getStateChecksum(struct Position s) {
	uint32_t sum = 0;
	uint8_t *p = (uint8_t*) &s;
	for (int i = 0; i < sizeof(s); i++) {
		sum += p[i];
	}

	return sum;
}

void SaveState() {
	if (ee24_isConnected()) {
		uint32_t sum = getStateChecksum(state.position);
		uint8_t *sum_p = (uint8_t*) &sum;
		ee24_write(0, sum_p, sizeof(sum), 1000);
		uint8_t *state_p = (uint8_t*) &state.position;
		ee24_write(sizeof(sum), state_p, sizeof(state.position), 1000);
	}
}

void LoadState() {
	if (ee24_isConnected()) {
		uint32_t sum = 0;
		struct Position readState;

		uint8_t *sum_p = (uint8_t*) &sum;
		ee24_read(0, sum_p, sizeof(sum), 1000);

		uint8_t *state_p = (uint8_t*) &readState;
		ee24_read(sizeof(sum), state_p, sizeof(readState), 1000);

		uint32_t calculatedChecksum = getStateChecksum(readState);
		if (calculatedChecksum == sum) {
			state.position = readState;
		}
	}
}
