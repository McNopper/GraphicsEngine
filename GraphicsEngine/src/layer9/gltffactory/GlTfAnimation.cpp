/*
 * GlTfAnimation.cpp
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#include "GlTfAnimation.h"

using namespace std;

GlTfAnimation::GlTfAnimation() :
		startTime(0.0f), stopTime(0.0f), allChannels()
{
}

GlTfAnimation::~GlTfAnimation()
{
}

float GlTfAnimation::getStartTime() const
{
	return startTime;
}

void GlTfAnimation::setStartTime(float startTime)
{
	this->startTime = startTime;
}

float GlTfAnimation::getStopTime() const
{
	return stopTime;
}

void GlTfAnimation::setStopTime(float stopTime)
{
	this->stopTime = stopTime;
}

void GlTfAnimation::addChannel(const GlTfChannelSP& channel)
{
	allChannels.push_back(channel);
}

const vector<GlTfChannelSP>& GlTfAnimation::getAllChannels() const
{
	return allChannels;
}

