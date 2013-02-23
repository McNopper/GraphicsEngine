/*
 * FrameCounter.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "FrameCounter.h"

FrameCounter::FrameCounter() :
		numberFrames(0.0f), elapsedTime(0.0f), framesPerSecondAsFloat(0.0f)
{
	framesPerSecondAsString[0] = '\0';
}

FrameCounter::~FrameCounter()
{
}

void FrameCounter::updateFramesPerSecond()
{
	if (elapsedTime != 0.0f)
	{
		framesPerSecondAsFloat = numberFrames / elapsedTime;

		sprintf(framesPerSecondAsString, "FPS: %.2f", framesPerSecondAsFloat);
	}
}

void FrameCounter::reset()
{
	numberFrames = 0.0f;

	elapsedTime = 0.0f;
}

void FrameCounter::increaseNumberFrames()
{
	numberFrames += 1.0f;
}

bool FrameCounter::increaseElapsedTime(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= 1.0f)
	{
		return true;
	}

	return false;
}

float FrameCounter::calulateFramesPerSecondAsFloat()
{
	if (elapsedTime >= 1.0f)
	{
		updateFramesPerSecond();

		reset();
	}

	return framesPerSecondAsFloat;
}

const char* FrameCounter::calculateFramesPerSecondAsString()
{
	if (elapsedTime >= 1.0f)
	{
		updateFramesPerSecond();

		reset();
	}

	return framesPerSecondAsString;
}
