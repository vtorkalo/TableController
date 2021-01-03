#ifndef POWER_H
#define POWER_H

#include <stdint.h>

void TurnOnLeft(void);
void TurnOnRight(void);
void FindZero(void);
void updateCurrent(void);
void goToPos(int16_t pos);
void motorStop(void);
void handleMotorBeep(void);
void updateBridgeState(void);
void SetHighSpeed(void);
void SetLowSpeed(void);

#endif
