/*
 * TextureCubeMap.cpp
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#include "TextureCubeMap.h"

using namespace std;

TextureCubeMap::TextureCubeMap(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixelsPosX, const uint8_t* pixelsNegX, const uint8_t* pixelsPosY, const uint8_t* pixelsNegY, const uint8_t* pixelsPosZ, const uint8_t* pixelsNegZ, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
		TextureStandard(identifier, GL_TEXTURE_CUBE_MAP, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic)
{
	pixelData[0] = PixelData(width, height, format, type, pixelsPosX, sizeOfData);
	pixelData[1] = PixelData(width, height, format, type, pixelsNegX, sizeOfData);
	pixelData[2] = PixelData(width, height, format, type, pixelsPosY, sizeOfData);
	pixelData[3] = PixelData(width, height, format, type, pixelsNegY, sizeOfData);
	pixelData[4] = PixelData(width, height, format, type, pixelsPosZ, sizeOfData);
	pixelData[5] = PixelData(width, height, format, type, pixelsNegZ, sizeOfData);

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

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internalFormat, width, height, 0, format, type, pixelData[0].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internalFormat, width, height, 0, format, type, pixelData[1].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelData[2].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelData[3].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelData[4].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelData[5].getPixels());

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
	for (int32_t i = 0; i < 6; i++)
	{
		pixelData[i].freePixels();
	}
}

const PixelData& TextureCubeMap::getPixelData(int32_t index) const
{
	if (index < 0 || index > 5)
	{
		throw "Index out of bounds";
	}

	return pixelData[index];
}
