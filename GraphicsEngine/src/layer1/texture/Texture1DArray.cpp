/*
 * Texture1DArray.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "Texture1DArray.h"

using namespace std;

Texture1DArray::Texture1DArray(const string& identifier, GLint internalFormat, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
	TextureStandard(identifier, GL_TEXTURE_1D_ARRAY, internalFormat, width, 1, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic)
{
	init();
}

Texture1DArray::~Texture1DArray()
{
	freePixels();
}

bool Texture1DArray::init()
{
	if (width < 1 || height != 1 || allPixelData.size() < 1)
	{
		return false;
	}

	if (textureName)
	{
		destroy();
	}

	glGenTextures(1, &textureName);

	if (!textureName)
	{
		return false;
	}

	glBindTexture(target, textureName);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(target, 0, internalFormat, width, allPixelData.size(), 0, format, type, nullptr);

	auto walker = allPixelData.begin();
	int32_t index = 0;
	while (walker != allPixelData.end())
	{
		glTexSubImage2D(target, 0, 0, index, (*walker)->getWidth(), 1, format, type, (*walker)->getPixels());

		walker++;
		index++;
	}

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

void Texture1DArray::freePixels()
{
	auto walker = allPixelData.begin();
	while (walker != allPixelData.end())
	{
		walker->reset();
		walker++;
	}
	allPixelData.clear();
}

bool Texture1DArray::addPixelData(const PixelDataSP& pixelData)
{
	if (!pixelData.get())
	{
		return false;
	}

	if (pixelData->getWidth() > width || pixelData->getHeight() != 1 || pixelData->getFormat() != format || pixelData->getType() != type)
	{
		return false;
	}

	allPixelData.push_back(pixelData);

	return true;
}
