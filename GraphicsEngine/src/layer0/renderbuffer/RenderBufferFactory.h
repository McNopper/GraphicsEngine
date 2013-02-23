/*
 * RenderBufferFactory.h
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#ifndef RENDERBUFFERFACTORY_H_
#define RENDERBUFFERFACTORY_H_

#include "../../UsedLibs.h"

#include "RenderBuffer.h"
#include "RenderBufferMultisample.h"

class RenderBufferFactory
{
public:
	RenderBufferFactory();
	virtual ~RenderBufferFactory();

	RenderBufferSP createRenderBuffer(GLenum internalFormat, boost::int32_t width, boost::int32_t height) const;

	RenderBufferMultisampleSP createRenderBufferMultisample(boost::int32_t samples, GLenum internalFormat, boost::int32_t width, boost::int32_t height) const;

};

#endif /* RENDERBUFFERFACTORY_H_ */
