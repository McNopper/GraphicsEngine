/*
 * TextureCubeMap.cpp
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#include "TextureCubeMap.h"

using namespace boost;

TextureCubeMap::TextureCubeMap(GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type,
		const uint8_t* pixelsPosX, const uint8_t* pixelsNegX, const uint8_t* pixelsPosY, const uint8_t* pixelsNegY, const uint8_t* pixelsPosZ, const uint8_t* pixelsNegZ,
		uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) :
		TextureStandard(GL_TEXTURE_CUBE_MAP, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT)
{
	if (pixelsPosX && pixelsNegX && pixelsPosY && pixelsNegY && pixelsPosZ && pixelsNegZ && sizeOfData > 0)
	{
		this->pixelsPosX = new uint8_t[sizeOfData];
		if (this->pixelsPosX)
		{
			memcpy(this->pixelsPosX, pixelsPosX, sizeOfData);
		}
		this->pixelsNegX =  new uint8_t[sizeOfData];
		if (this->pixelsNegX)
		{
			memcpy(this->pixelsNegX, pixelsNegX, sizeOfData);
		}
		this->pixelsPosY = new uint8_t[sizeOfData];
		if (this->pixelsPosY)
		{
			memcpy(this->pixelsPosY, pixelsPosY, sizeOfData);
		}
		this->pixelsNegY = new uint8_t[sizeOfData];
		if (this->pixelsNegY)
		{
			memcpy(this->pixelsNegY, pixelsNegY, sizeOfData);
		}
		this->pixelsPosZ = new uint8_t[sizeOfData];
		if (this->pixelsPosZ)
		{
			memcpy(this->pixelsPosZ, pixelsPosZ, sizeOfData);
		}
		this->pixelsNegZ = new uint8_t[sizeOfData];
		if (this->pixelsNegZ)
		{
			memcpy(this->pixelsNegZ, pixelsNegZ, sizeOfData);
		}
	}
	else
	{
		this->pixelsPosX = nullptr;
		this->pixelsNegX = nullptr;
		this->pixelsPosY = nullptr;
		this->pixelsNegY = nullptr;
		this->pixelsPosZ = nullptr;
		this->pixelsNegZ = nullptr;
	}

	init();
}

TextureCubeMap::~TextureCubeMap()
{
	freePixels();
}


bool TextureCubeMap::init()
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

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internalFormat, width, height, 0, format, type, pixelsPosX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internalFormat, width, height, 0, format, type, pixelsNegX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelsPosY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelsNegY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelsPosZ);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelsNegZ);

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

void TextureCubeMap::freePixels()
{
	if (pixelsPosX)
	{
		delete[] pixelsPosX;

		pixelsPosX = nullptr;
	}
	if (pixelsNegX)
	{
		delete[] pixelsNegX;

		pixelsNegX = nullptr;
	}
	if (pixelsPosY)
	{
		delete[] pixelsPosY;

		pixelsPosY = nullptr;
	}
	if (pixelsNegY)
	{
		delete[] pixelsNegY;

		pixelsNegY = nullptr;
	}
	if (pixelsPosZ)
	{
		delete[] pixelsPosZ;

		pixelsPosZ = nullptr;
	}
	if (pixelsNegZ)
	{
		delete[] pixelsNegZ;

		pixelsNegZ = nullptr;
	}
}
