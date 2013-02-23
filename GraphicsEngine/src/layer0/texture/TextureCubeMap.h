/*
 * TextureCubeMap.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef TEXTURECUBEMAP_H_
#define TEXTURECUBEMAP_H_

#include "TextureStandard.h"

class TextureCubeMap : public TextureStandard
{

private:

	boost::uint8_t* pixelsPosX;
	boost::uint8_t* pixelsNegX;
	boost::uint8_t* pixelsPosY;
	boost::uint8_t* pixelsNegY;
	boost::uint8_t* pixelsPosZ;
	boost::uint8_t* pixelsNegZ;

public:

	TextureCubeMap(GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, const boost::uint8_t* pixelsPosX, const boost::uint8_t* pixelsNegX, const boost::uint8_t* pixelsPosY, const boost::uint8_t* pixelsNegY, const boost::uint8_t* pixelsPosZ, const boost::uint8_t* pixelsNegZ, boost::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
	virtual ~TextureCubeMap();

	virtual bool init();

	virtual void freePixels();

};

typedef boost::shared_ptr<TextureCubeMap> TextureCubeMapSP;

#endif /* TEXTURECUBEMAP_H_ */
