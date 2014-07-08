/*
 * GlTfAnimation.cpp
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#include "GlTfAnimation.h"

using namespace std;

GlTfAnimation::GlTfAnimation() :
		allChannels()
{
}

GlTfAnimation::~GlTfAnimation()
{
}

void GlTfAnimation::addChannel(const GlTfChannelSP& channel)
{
	allChannels.push_back(channel);
}

const vector<GlTfChannelSP>& GlTfAnimation::getAllChannels() const
{
	return allChannels;
}

