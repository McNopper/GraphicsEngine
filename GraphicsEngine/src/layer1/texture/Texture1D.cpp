/*
 * Texture1D.cpp
 *
 *  Created on: 20.12.2012
 *      Author: nopper
 */

#include "Texture1D.h"

using namespace std;

Texture1D::Texture1D(const std::string& identifier, float red) :
	TextureStandard(identifier, GL_TEXTURE_1D, red), pixelData(1, 1, GL_RGBA, GL_FLOAT, (const uint8_t*)&red, sizeof(float))
{
	init();
}

Texture1D::Texture1D(const string& identifier, const Color& color) :
	TextureStandard(identifier, GL_TEXTURE_1D, color), pixelData(1, 1, GL_RGBA, GL_FLOAT, (const uint8_t*)color.getRGBA(), sizeof(Color))
{
	init();
}

Texture1D::Texture1D(const string& identifier, GLint internalFormat, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
	TextureStandard(identifier, GL_TEXTURE_1D, internalFormat, width, 1, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic), pixelData(width, 1, format, type, pixels, sizeOfData)
{
	init();
}

Texture1D::~Texture1D()
{
	freePixels();
}

bool Texture1D::init()
{
	if (width < 1 || height != 1)
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

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage1D(target, 0, internalFormat, width, 0, format, type, pixelData.getPixels());

	if (mipMap)
	{
		glGenerateMipmap(target);
	}

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);

	return true;
}

void Texture1D::freePixels()
{
	pixelData.freePixels();
}
