/*
 * RenderBuffer.cpp
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#include "RenderBuffer.h"

using namespace std;

RenderBuffer::RenderBuffer(GLenum internalFormat, int32_t width, int32_t height) :
		internalFormat(internalFormat), width(width), height(height), rb(0), valid(false)
{
	init();
}

RenderBuffer::~RenderBuffer()
{
	destroy();
}

bool RenderBuffer::init()
{
	if (width < 1 || height < 1)
	{
		return false;
	}

	if (!rb)
	{
		glGenRenderbuffers(1, &rb);

		if (!rb)
		{
			return false;
		}
	}

	glBindRenderbuffer(GL_RENDERBUFFER, rb);

	glGetError();

	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);

	valid = (glGetError() == GL_NO_ERROR);

	return valid;
}

void RenderBuffer::destroy()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (rb)
	{
		glDeleteRenderbuffers(1, &rb);

		rb = 0;
	}
}

bool RenderBuffer::isMultisample() const
{
	return false;
}

GLenum RenderBuffer::getInternalFormat() const
{
	return internalFormat;
}

void RenderBuffer::setInternalFormat(GLenum internalFormat)
{
	this->internalFormat = internalFormat;

	init();
}

std::int32_t RenderBuffer::getWidth() const
{
	return width;
}

void RenderBuffer::setWidth(int32_t width)
{
	if (width != this->width)
	{
		this->width = width;

		init();
	}
}

std::int32_t RenderBuffer::getHeight() const
{
	return height;
}

void RenderBuffer::setHeight(int32_t height)
{
	if (height != this->height)
	{
		this->height = height;

		init();
	}
}

void RenderBuffer::setWidthHeight(int32_t width, int32_t height)
{
	if (width != this->width || height != this->height)
	{
		this->width = width;
		this->height = height;

		init();
	}
}

GLuint RenderBuffer::getRb() const
{
	return rb;
}

bool RenderBuffer::isValid() const
{
	return valid;
}
