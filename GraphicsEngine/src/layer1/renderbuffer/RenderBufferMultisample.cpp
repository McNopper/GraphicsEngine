/*
 * RenderBufferMultisample.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "RenderBufferMultisample.h"

using namespace std;

RenderBufferMultisample::RenderBufferMultisample(int32_t samples, GLenum internalFormat, int32_t width, int32_t height) :
		RenderBuffer(internalFormat, width, height), samples(samples)
{
	init();
}

RenderBufferMultisample::~RenderBufferMultisample()
{
}

bool RenderBufferMultisample::init()
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

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height);

	valid = (glGetError() == GL_NO_ERROR);

	return valid;
}

bool RenderBufferMultisample::isMultisample() const
{
	return samples > 0;
}


