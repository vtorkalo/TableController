#ifndef PERIOD_CIRCLE_BUFFER_H
#define PERIOD_CIRCLE_BUFFER_H

#include "stdint.h"

#define CIRCLE_BUFFER_SIZE 10

void StoreMeasurment(uint32_t value);

uint16_t GetRecordsCount();

uint32_t GetMeasurement(uint16_t index);
void UpdateLast(uint32_t value);

#endif
