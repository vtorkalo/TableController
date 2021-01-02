#ifndef APP_STATE_H
#define APP_STATE_H

#include <stdint.h>
#include <stdbool.h>

enum RotationDirection
{
	NONE,
	LEFT,
	RIGHT
};

enum CurrentAction
{
	IDLE,
	FIND_ZERO,
	FIND_MAX,
	FIND_POS,
	MOVE_LEFT,
	MOVE_RIGHT
};

struct Position
{
	int16_t motor1pos;
	int16_t motor1maxpos;
	int16_t motor1memory1;
	int16_t motor1memory2;
	int16_t motor1memory3;
};

struct AppState
{
	int16_t motor1targetpos;
	struct Position position;

	uint8_t motor1speed;
	int16_t motor1current;

	bool powerFailureFlag;
	bool powerFailureStateStored;
	bool motorBeepFlag;

	enum RotationDirection motorDirection;
	enum CurrentAction currentAction;
};
struct AppState state;
uint8_t saveStateFlag;

void initAppState(void);
void SaveState(void);
void LoadState(void);

#endif