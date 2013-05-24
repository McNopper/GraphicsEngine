/*
 * AnimationStack.cpp
 *
 *  Created on: 16.07.2012
 *      Author: nopper
 */

#include "AnimationStack.h"

using namespace std;
using namespace boost;

AnimationStack::AnimationStack(float startTime, float stopTime) :
		startTime(startTime), stopTime(stopTime), allAnimationLayers()
{
}

AnimationStack::~AnimationStack()
{
	vector<AnimationLayerSP>::iterator walker = allAnimationLayers.begin();

	while (walker != allAnimationLayers.end())
	{
		walker->reset();

		walker++;
	}

	allAnimationLayers.clear();
}

void AnimationStack::addAnimationLayer(const AnimationLayerSP& animationLayer)
{
	allAnimationLayers.push_back(animationLayer);
}

int32_t AnimationStack::getAnimationLayersCount() const
{
	return allAnimationLayers.size();
}

float AnimationStack::getStartTime() const
{
	return startTime;
}

float AnimationStack::getStopTime() const
{
	return stopTime;
}

const AnimationLayerSP& AnimationStack::getAnimationLayer(int32_t index) const
{
	return allAnimationLayers[index];
}
