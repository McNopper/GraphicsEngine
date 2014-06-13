/*
 * Texture2DMultisample.cpp
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#include "Texture2DMultisample.h"

using namespace std;

Texture2DMultisample::Texture2DMultisample(const string& identifier, int32_t samples, GLint internalFormat, int32_t width, int32_t height, bool fixedsamplelocations) :
		Texture(identifier, GL_TEXTURE_2D_MULTISAMPLE, internalFormat, width, height), samples(samples), fixedsamplelocations(fixedsamplelocations)
{
	init();
}

Texture2DMultisample::~Texture2DMultisample()
{
}

void Texture2DMultisample::changingSize()
{
	// Do nothing for now
}

bool Texture2DMultisample::init()
{
	if (width < 1 || height < 1)
	{
		return false;
	}

	if (!textureName)
	{
		glGenTextures(1, &textureName);

		if (!textureName)
		{
			return false;
		}
	}

	glBindTexture(target, textureName);

	glTexImage2DMultisample(target, samples, internalFormat, width, height, fixedsamplelocations);

	return true;
}
