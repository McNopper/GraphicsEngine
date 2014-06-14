/*
 * TextureCubeMap.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef TEXTURECUBEMAP_H_
#define TEXTURECUBEMAP_H_

#include "PixelData.h"
#include "TextureStandard.h"

class TextureCubeMap : public TextureStandard
{

private:

	PixelData pixelData[6];

public:

	TextureCubeMap(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixelsPosX, const std::uint8_t* pixelsNegX, const std::uint8_t* pixelsPosY, const std::uint8_t* pixelsNegY, const std::uint8_t* pixelsPosZ, const std::uint8_t* pixelsNegZ, std::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~TextureCubeMap();

	virtual bool init();

	virtual void freePixels();

	const PixelData& getPixelData(std::int32_t index) const;

};

typedef std::shared_ptr<TextureCubeMap> TextureCubeMapSP;

#endif /* TEXTURECUBEMAP_H_ */
