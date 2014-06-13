/*
 * FrameBufferBase.cpp
 *
 *  Created on: 10.04.2013
 *      Author: nopper
 */

#include "FrameBufferBase.h"

using namespace std;

FrameBufferBase::FrameBufferBase(int32_t width, int32_t height) :
	fbo(0), width(width), height(height), drawBufferMode(GL_FRONT), readBufferMode(GL_FRONT)
{
}

FrameBufferBase::~FrameBufferBase()
{
	destroy();
}

void FrameBufferBase::destroy()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (fbo)
	{
    	glDeleteFramebuffers(1, &fbo);

	    fbo = 0;
	}
}

GLuint FrameBufferBase::getFBO() const
{
	return fbo;
}

std::int32_t FrameBufferBase::getWidth() const
{
	return width;
}

void FrameBufferBase::setWidth(int32_t width)
{
	if (this->width != width)
	{
		this->width = width;
		destroy();

		init();
	}
}

std::int32_t FrameBufferBase::getHeight() const
{
	return height;
}

void FrameBufferBase::setHeight(int32_t height)
{
	if (this->height != height)
	{
		this->height = height;
		destroy();

		init();
	}
}

void FrameBufferBase::setWidthHeight(int32_t width, int32_t height)
{
	if (this->width != width || this->height != height)
	{
		this->width = width;
		this->height = height;
		destroy();

		init();
	}
}

GLenum FrameBufferBase::getDrawBufferMode() const
{
	return drawBufferMode;
}

void FrameBufferBase::setDrawBufferMode(GLenum drawBufferMode)
{
	this->drawBufferMode = drawBufferMode;

	init();
}

GLenum FrameBufferBase::getReadBufferMode() const
{
	return readBufferMode;
}

void FrameBufferBase::setReadBufferMode(GLenum readBufferMode)
{
	this->readBufferMode = readBufferMode;

	init();
}

bool FrameBufferBase::isValid() const
{
	if (!fbo)
	{
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	bool valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return valid;
}


