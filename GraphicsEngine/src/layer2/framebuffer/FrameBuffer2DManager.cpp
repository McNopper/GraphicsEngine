/*
 * FrameBuffer2DManager.cpp
 *
 *  Created on: 28.11.2012
 *      Author: nopper
 */

#include "FrameBuffer2DManager.h"

using namespace std;

FrameBuffer2DManager::FrameBuffer2DManager() :
	Singleton<FrameBuffer2DManager>(), allFrameBuffers(), allWindowFrameBuffers()
{
}

FrameBuffer2DManager::~FrameBuffer2DManager()
{
	auto walker = allFrameBuffers.begin();
	while (walker != allFrameBuffers.end())
	{
		walker->second.reset();
		walker++;
	}
	allFrameBuffers.clear();
	allWindowFrameBuffers.clear();
}

bool FrameBuffer2DManager::containsFrameBuffer(const string& key) const
{
	return allFrameBuffers.contains(key);
}

const FrameBuffer2DSP& FrameBuffer2DManager::getFrameBuffer(const string& key) const
{
	return allFrameBuffers.at(key);
}

void FrameBuffer2DManager::addFrameBuffer(const string& key, const FrameBuffer2DSP& framBuffer2D, bool windowFrameBuffer)
{
	allFrameBuffers[key] = framBuffer2D;

	if (windowFrameBuffer)
	{
		allWindowFrameBuffers[key] = framBuffer2D;
	}
}

FrameBuffer2DSP FrameBuffer2DManager::createFrameBuffer(const string& key, int32_t width, int32_t height, bool windowFrameBuffer)
{
	if (!allFrameBuffers.contains(key))
	{
		allFrameBuffers[key] = FrameBuffer2DSP(new FrameBuffer2D(width, height));

		if (windowFrameBuffer)
		{
			allWindowFrameBuffers[key] = allFrameBuffers[key];
		}

		return allFrameBuffers[key];
	}

	return allFrameBuffers[key];
}

void FrameBuffer2DManager::updateWidthHeight(int32_t width, int32_t height)
{
	auto walker = allWindowFrameBuffers.begin();

	while (walker != allWindowFrameBuffers.end())
	{
		walker->second->setWidthHeight(width, height);

		walker++;
	}
}
