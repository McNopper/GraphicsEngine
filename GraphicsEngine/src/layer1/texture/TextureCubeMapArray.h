/*
 * TextureCubeMapArray.h
 *
 *  Created on: 14.06.2014
 *      Author: nopper
 */

#ifndef TEXTURECUBEMAPARRAY_H_
#define TEXTURECUBEMAPARRAY_H_

#include "PixelData.h"
#include "TextureStandard.h"

class TextureCubeMapArray : public TextureStandard
{

private:

	PixelDataSP pixelData;

public:
	TextureCubeMapArray(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixelsPosX[], const std::uint8_t* pixelsNegX[], const std::uint8_t* pixelsPosY[], const std::uint8_t* pixelsNegY[], const std::uint8_t* pixelsPosZ[], const std::uint8_t* pixelsNegZ[], std::uint32_t sizeOfData, std::uint32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~TextureCubeMapArray();

	// TODO Implement functions.

};

#endif /* TEXTURECUBEMAPARRAY_H_ */
