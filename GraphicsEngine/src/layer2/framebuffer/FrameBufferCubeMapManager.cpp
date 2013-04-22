/*
 * FrameBufferCubeMapManager.cpp
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#include "FrameBufferCubeMapManager.h"

using namespace std;

using namespace boost;

FrameBufferCubeMapManager* FrameBufferCubeMapManager::instance = nullptr;

FrameBufferCubeMapManager::FrameBufferCubeMapManager() :
		allFrameBuffers()
{
}

FrameBufferCubeMapManager::~FrameBufferCubeMapManager()
{
	auto walker = allFrameBuffers.begin();
	while (walker != allFrameBuffers.end())
	{
		walker->second.reset();
		walker++;
	}
	allFrameBuffers.clear();
}

FrameBufferCubeMapManager* FrameBufferCubeMapManager::getInstance()
{
	if (!instance)
	{
		instance = new FrameBufferCubeMapManager();
	}

	return instance;
}

void FrameBufferCubeMapManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool FrameBufferCubeMapManager::containsFrameBuffer(const string& key) const
{
	return allFrameBuffers.find(key) != allFrameBuffers.end();
}

const FrameBufferCubeMapSP& FrameBufferCubeMapManager::getFrameBuffer(const string& key) const
{
	return allFrameBuffers.at(key);
}

void FrameBufferCubeMapManager::addFrameBuffer(const string& key, const FrameBufferCubeMapSP& framBufferCubeMap)
{
	allFrameBuffers[key] = framBufferCubeMap;
}

FrameBufferCubeMapSP FrameBufferCubeMapManager::createFrameBuffer(const string& key, int32_t width, int32_t height)
{
	auto walker = allFrameBuffers.find(key);

	if (walker == allFrameBuffers.end())
	{
		allFrameBuffers[key] = FrameBufferCubeMapSP(new FrameBufferCubeMap(width, height));

		return allFrameBuffers[key];
	}

	return allFrameBuffers[key];
}
