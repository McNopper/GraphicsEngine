/*
 * FrameCounter.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef FRAMECOUNTER_H_
#define FRAMECOUNTER_H_

class FrameCounter
{

private:

	float numberFrames;

	float elapsedTime;

	float framesPerSecondAsFloat;

	char framesPerSecondAsString[32];

	void updateFramesPerSecond();

public:
	FrameCounter();
	virtual ~FrameCounter();

	void reset();

	void increaseNumberFrames();

	bool increaseElapsedTime(float deltaTime);

	float calulateFramesPerSecondAsFloat();

	const char* calculateFramesPerSecondAsString();

};

#endif /* FRAMECOUNTER_H_ */
