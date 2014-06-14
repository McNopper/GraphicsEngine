/*
 * TextureCubeMapArray.cpp
 *
 *  Created on: 14.06.2014
 *      Author: nopper
 */

#include "TextureCubeMapArray.h"

using namespace std;

TextureCubeMapArray::TextureCubeMapArray(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixelsPosX[], const uint8_t* pixelsNegX[], const uint8_t* pixelsPosY[], const uint8_t* pixelsNegY[], const uint8_t* pixelsPosZ[], const uint8_t* pixelsNegZ[], uint32_t sizeOfData, uint32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
		TextureStandard(identifier, GL_TEXTURE_CUBE_MAP_ARRAY, internalFormat, width, height, format, type, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic)
{
	PixelData* pointerPixelData = new PixelData[6 * sizeOfArray];

	if (!pointerPixelData)
	{
		return;
	}

	//

	for (uint32_t i = 0; i < sizeOfArray; i++)
	{
		pointerPixelData[i*6+0] = PixelData(width, height, format, type, pixelsPosX[i], sizeOfData);
		pointerPixelData[i*6+1] = PixelData(width, height, format, type, pixelsNegX[i], sizeOfData);
		pointerPixelData[i*6+2] = PixelData(width, height, format, type, pixelsPosY[i], sizeOfData);
		pointerPixelData[i*6+3] = PixelData(width, height, format, type, pixelsNegY[i], sizeOfData);
		pointerPixelData[i*6+4] = PixelData(width, height, format, type, pixelsPosZ[i], sizeOfData);
		pointerPixelData[i*6+5] = PixelData(width, height, format, type, pixelsNegZ[i], sizeOfData);
	}

	//

	pixelData = PixelDataSP(pointerPixelData, DELETE_ARRAY_PixelDataSP);

	// TODO Initialize.
}

TextureCubeMapArray::~TextureCubeMapArray()
{
	// TODO Free pixels.
}

