/*
 * RenderBufferFactory.cpp
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#include "RenderBufferFactory.h"

using namespace std;

RenderBufferFactory::RenderBufferFactory()
{
}

RenderBufferFactory::~RenderBufferFactory()
{
}

RenderBufferSP RenderBufferFactory::createRenderBuffer(GLenum internalFormat, int32_t width, int32_t height) const
{
	return RenderBufferSP(new RenderBuffer(internalFormat, width, height));
}

RenderBufferMultisampleSP RenderBufferFactory::createRenderBufferMultisample(int32_t samples, GLenum internalFormat, int32_t width, int32_t height) const
{
	return RenderBufferMultisampleSP(new RenderBufferMultisample(samples, internalFormat, width, height));
}
