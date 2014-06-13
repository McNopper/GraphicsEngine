/*
 * RenderBufferMultisampleManager.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "RenderBufferFactory.h"

#include "RenderBufferMultisampleManager.h"

using namespace std;

RenderBufferMultisampleManager::RenderBufferMultisampleManager() :
		Singleton<RenderBufferMultisampleManager>(), allRenderBuffers()
{
}

RenderBufferMultisampleManager::~RenderBufferMultisampleManager()
{
	auto walker = allRenderBuffers.begin();
	while (walker != allRenderBuffers.end())
	{
		walker->second.reset();

		walker++;
	}
	allRenderBuffers.clear();
}

void RenderBufferMultisampleManager::addRenderBuffer(const string& key, const RenderBufferMultisampleSP& renderBufferMultisample)
{
	allRenderBuffers[key] = renderBufferMultisample;
}

RenderBufferMultisampleSP RenderBufferMultisampleManager::createRenderBuffer(const string& key, int32_t samples, GLenum internalFormat, int32_t width, int32_t height)
{
	RenderBufferFactory renderBufferFactory;

	if (!allRenderBuffers.contains(key))
	{
		allRenderBuffers[key] = renderBufferFactory.createRenderBufferMultisample(samples, internalFormat, width, height);

		return allRenderBuffers[key];
	}

	return allRenderBuffers[key];
}
