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

	PixelData pixelDataPosX;
	PixelData pixelDataNegX;
	PixelData pixelDataPosY;
	PixelData pixelDataNegY;
	PixelData pixelDataPosZ;
	PixelData pixelDataNegZ;

public:

	TextureCubeMap(GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, const boost::uint8_t* pixelsPosX, const boost::uint8_t* pixelsNegX, const boost::uint8_t* pixelsPosY, const boost::uint8_t* pixelsNegY, const boost::uint8_t* pixelsPosZ, const boost::uint8_t* pixelsNegZ, boost::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~TextureCubeMap();

	virtual bool init();

	virtual void freePixels();

	const PixelData& getPixelData(boost::int32_t index) const;

};

typedef boost::shared_ptr<TextureCubeMap> TextureCubeMapSP;

#endif /* TEXTURECUBEMAP_H_ */
