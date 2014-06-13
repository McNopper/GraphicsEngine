/*
 * Texture2DArray.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "Texture2DArray.h"

using namespace std;

Texture2DArray::Texture2DArray(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
	TextureStandard(identifier, GL_TEXTURE_2D_ARRAY, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic)
{
	init();
}

Texture2DArray::~Texture2DArray()
{
	freePixels();
}

bool Texture2DArray::init()
{
	if (width < 1 || height < 1 || allPixelData.size() < 1)
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

	glTexImage3D(target, 0, internalFormat, width, height, allPixelData.size(), 0, format, type, nullptr);

	auto walker = allPixelData.begin();
	int32_t index = 0;
	while (walker != allPixelData.end())
	{
		if ((*walker)->getPixels())
		{
			glTexSubImage3D(target, 0, 0, 0, index, (*walker)->getWidth(), (*walker)->getHeight(), 1, format, type, (*walker)->getPixels());
		}

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

void Texture2DArray::freePixels()
{
	auto walker = allPixelData.begin();
	while (walker != allPixelData.end())
	{
		walker->reset();
		walker++;
	}
	allPixelData.clear();
}

bool Texture2DArray::addPixelData(const PixelDataSP& pixelData)
{
	if (!pixelData.get())
	{
		return false;
	}

	if (pixelData->getWidth() > width || pixelData->getHeight() > height || pixelData->getFormat() != format || pixelData->getType() != type)
	{
		return false;
	}

	allPixelData.push_back(pixelData);

	return true;
}
