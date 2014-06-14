/*
 * TextureCubeMapArray.cpp
 *
 *  Created on: 14.06.2014
 *      Author: nopper
 */

#include "TextureCubeMapArray.h"

using namespace std;

TextureCubeMapArray::TextureCubeMapArray(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixelsPos[], uint32_t sizeOfData, int32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
		TextureStandard(identifier, GL_TEXTURE_CUBE_MAP_ARRAY, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic), sizeOfArray(sizeOfArray)
{
	PixelData* pointerPixelData = new PixelData[6 * sizeOfArray];

	if (!pointerPixelData)
	{
		return;
	}

	//

	for (int32_t i = 0; i < sizeOfArray; i++)
	{
		for (int32_t k = 0; k < 6; k++)
		{
			pointerPixelData[i*6+0] = PixelData(width, height, format, type, pixelsPos[i * 6 + k], sizeOfData);
		}
	}

	//

	pixelData = PixelDataSP(pointerPixelData, DELETE_ARRAY_PixelDataSP);

	//

	init();
}

TextureCubeMapArray::~TextureCubeMapArray()
{
	freePixels();
}

bool TextureCubeMapArray::init()
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

	glTexImage3D(target, 0, internalFormat, width, height, 6*sizeOfArray, 0, format, type, 0);

    for (int32_t i = 0; i < sizeOfArray; i++)
    {
        for (int32_t k = 0; k < 6; k++)
        {
        	glTexSubImage3D(target, 0, 0, 0,  6*i + k, width, height, 1, format, type, pixelData.get()[i*6 + k].getPixels());
        }
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

void TextureCubeMapArray::freePixels()
{
	for (int32_t i = 0; i < sizeOfArray; i++)
	{
		for (int32_t k = 0; k < 6; k++)
		{
			pixelData.get()[i*6+k].freePixels();
		}
	}
}

const PixelData& TextureCubeMapArray::getPixelData(int32_t index, int32_t arrayIndex) const
{
	if (index < 0 || index > 5 || arrayIndex < 0 || arrayIndex >= this->sizeOfArray)
	{
		throw "Index out of bounds";
	}

	return pixelData.get()[arrayIndex*6+index];
}

int32_t TextureCubeMapArray::getSizeOfArray() const
{
	return sizeOfArray;
}

