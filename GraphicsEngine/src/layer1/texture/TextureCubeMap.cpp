/*
 * TextureCubeMap.cpp
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#include "TextureCubeMap.h"

using namespace boost;

TextureCubeMap::TextureCubeMap(GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixelsPosX, const uint8_t* pixelsNegX, const uint8_t* pixelsPosY, const uint8_t* pixelsNegY, const uint8_t* pixelsPosZ, const uint8_t* pixelsNegZ, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
		TextureStandard(GL_TEXTURE_CUBE_MAP, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic), pixelDataPosX(width, height, format, type, pixelsPosX, sizeOfData), pixelDataNegX(width, height, format, type, pixelsNegX, sizeOfData), pixelDataPosY(width, height, format, type, pixelsPosY, sizeOfData), pixelDataNegY(width, height, format, type, pixelsNegY, sizeOfData), pixelDataPosZ(width, height, format, type, pixelsPosZ, sizeOfData), pixelDataNegZ(width, height, format, type, pixelsNegZ, sizeOfData)
{
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

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internalFormat, width, height, 0, format, type, pixelDataPosX.getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internalFormat, width, height, 0, format, type, pixelDataNegX.getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelDataPosY.getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internalFormat, width, height, 0, format, type, pixelDataNegY.getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelDataPosZ.getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internalFormat, width, height, 0, format, type, pixelDataNegZ.getPixels());

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
	pixelDataPosX.freePixels();
	pixelDataNegX.freePixels();
	pixelDataPosY.freePixels();
	pixelDataNegY.freePixels();
	pixelDataPosZ.freePixels();
	pixelDataNegZ.freePixels();
}

const PixelData& TextureCubeMap::getPixelData(boost::int32_t index) const
{
	switch (index)
	{
		case 0:
			// Do later
		break;
		case 1:
			return pixelDataNegX;
		break;
		case 2:
			return pixelDataPosY;
		break;
		case 3:
			return pixelDataNegY;
		break;
		case 4:
			return pixelDataPosZ;
		break;
		case 5:
			return pixelDataNegZ;
		break;
		default:
			throw "Index out of bounds";
		break;
	}

	return pixelDataPosX;
}
