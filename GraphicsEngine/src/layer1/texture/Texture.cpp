/*
 * Texture.cpp
 *
 *  Created on: 23.11.2012
 *      Author: nopper
 */

#include "Texture.h"

using namespace std;

Texture::Texture(const string& identifier, GLenum target, GLint internalFormat, int32_t width, int32_t height) :
		identifier(identifier), target(target), internalFormat(internalFormat), width(width), height(height), textureName(0)
{

}

Texture::~Texture()
{
	destroy();
}

void Texture::destroy()
{
	glBindTexture(target, 0);

	if (textureName)
	{
		glDeleteTextures(1, &textureName);

		textureName = 0;
	}
}

int32_t Texture::getWidth() const
{
	return width;
}

void Texture::setWidth(int32_t width)
{
	if (width != this->width)
	{
		destroy();

		changingSize();

		this->width = width;

		init();
	}
}

int32_t Texture::getHeight() const
{
	return height;
}

void Texture::setHeight(int32_t height)
{
	if (height != this->height)
	{
		destroy();

		changingSize();

		this->height = height;

		init();
	}
}

void Texture::setWidthHeight(int32_t width, int32_t height)
{
	if (width != this->width || height != this->height)
	{
		destroy();

		changingSize();

		this->width = width;
		this->height = height;

		init();
	}
}

const string& Texture::getIdentifier() const
{
	return identifier;
}

GLenum Texture::getTarget() const
{
	return target;
}

GLuint Texture::getTextureName() const
{
	return textureName;
}

GLint Texture::getInternalFormat() const
{
	return internalFormat;
}

void Texture::setInternalFormat(GLint internalFormat)
{
	if (internalFormat != this->internalFormat)
	{
		destroy();

		this->internalFormat = internalFormat;

		init();
	}
}
