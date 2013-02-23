/*
 * RenderBufferManager.cpp
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#include "RenderBufferFactory.h"

#include "RenderBufferManager.h"

using namespace std;
using namespace boost;

RenderBufferManager* RenderBufferManager::instance = nullptr;

RenderBufferManager::RenderBufferManager() :
		allRenderBuffers()
{
}

RenderBufferManager::~RenderBufferManager()
{
	auto walker = allRenderBuffers.begin();
	while (walker != allRenderBuffers.end())
	{
		walker->second.reset();

		walker++;
	}
	allRenderBuffers.clear();
}

RenderBufferManager* RenderBufferManager::getInstance()
{
	if (!instance)
	{
		instance = new RenderBufferManager();
	}

	return instance;
}

void RenderBufferManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void RenderBufferManager::addRenderBuffer(const string& key, const RenderBufferSP& renderBuffer)
{
	allRenderBuffers[key] = renderBuffer;
}

RenderBufferSP RenderBufferManager::createRenderBuffer(const string& key, GLenum internalFormat, int32_t width, int32_t height)
{
	auto walker = allRenderBuffers.find(key);

	RenderBufferFactory renderBufferFactory;

	if (walker == allRenderBuffers.end())
	{
		allRenderBuffers[key] = renderBufferFactory.createRenderBuffer(internalFormat, width, height);

		return allRenderBuffers[key];
	}

	return allRenderBuffers[key];
}


