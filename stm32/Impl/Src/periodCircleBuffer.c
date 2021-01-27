#include "appState.h"
#include "periodCircleBuffer.h"

static uint16_t nextIndex = 0;
static _Bool isBufferFull = 0;
uint32_t circleBuffer[CIRCLE_BUFFER_SIZE];

void StoreMeasurment(uint32_t value)
{
	if (nextIndex < CIRCLE_BUFFER_SIZE)
	{
		circleBuffer[nextIndex] = value;
		nextIndex++;
	}
	else
	{
		nextIndex = 0;
		isBufferFull = 1;
	}
}

void ClearBuffer(void)
{
	isBufferFull = 0;
	nextIndex = 0;
}

uint16_t GetRecordsCount()
{
	return isBufferFull ? CIRCLE_BUFFER_SIZE : nextIndex;
}

void UpdateLast(uint32_t value)
{
	if (nextIndex > 0)
	{
		circleBuffer[nextIndex-1] = value;
	}
	else
	{
		circleBuffer[CIRCLE_BUFFER_SIZE - 1 ] = value;
	}
}

uint32_t GetMeasurement(uint16_t index)
{
	if (!isBufferFull)
	{
		return circleBuffer[index];
	}
	else
	{
		uint16_t bufferIndex = nextIndex + index;
		if (bufferIndex > CIRCLE_BUFFER_SIZE-1)
		{
			bufferIndex -= CIRCLE_BUFFER_SIZE;
		}
		return circleBuffer[bufferIndex];
	}
}

