/*
 * Texture1D.h
 *
 *  Created on: 20.12.2012
 *      Author: nopper
 */

#ifndef TEXTURE1D_H_
#define TEXTURE1D_H_

#include "PixelData.h"
#include "TextureStandard.h"

class Texture1D: public TextureStandard
{

private:

	PixelData pixelData;

public:

	Texture1D(const std::string& identifier, float red);
	Texture1D(const std::string& identifier, const Color& color);
	Texture1D(const std::string& identifier, GLint internalFormat, std::int32_t width, GLenum format, GLenum type, const std::uint8_t* pixels, std::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~Texture1D();

	virtual bool init();

	virtual void freePixels();

};

typedef std::shared_ptr<Texture1D> Texture1DSP;

#endif /* TEXTURE1D_H_ */
