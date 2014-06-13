/*
 * RenderBufferManager.cpp
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#include "RenderBufferFactory.h"

#include "RenderBufferManager.h"

using namespace std;

RenderBufferManager::RenderBufferManager() :
		Singleton<RenderBufferManager>(), allRenderBuffers()
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

void RenderBufferManager::addRenderBuffer(const string& key, const RenderBufferSP& renderBuffer)
{
	allRenderBuffers[key] = renderBuffer;
}

RenderBufferSP RenderBufferManager::createRenderBuffer(const string& key, GLenum internalFormat, int32_t width, int32_t height)
{
	RenderBufferFactory renderBufferFactory;

	if (!allRenderBuffers.contains(key))
	{
		allRenderBuffers[key] = renderBufferFactory.createRenderBuffer(internalFormat, width, height);

		return allRenderBuffers[key];
	}

	return allRenderBuffers[key];
}


