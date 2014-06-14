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

	std::int32_t sizeOfArray;

	PixelDataSP pixelData;

public:
	TextureCubeMapArray(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixelsPos[], std::uint32_t sizeOfData, std::int32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~TextureCubeMapArray();

	virtual bool init();

	virtual void freePixels();

	const PixelData& getPixelData(std::int32_t index, std::int32_t arrayIndex) const;

	std::int32_t getSizeOfArray() const;

};

typedef std::shared_ptr<TextureCubeMapArray> TextureCubeMapArraySP;

#endif /* TEXTURECUBEMAPARRAY_H_ */
