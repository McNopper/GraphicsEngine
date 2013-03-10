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

	Texture1D(GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, const boost::uint8_t* pixels, boost::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
	virtual ~Texture1D();

	virtual bool init();

	virtual void freePixels();

};

typedef boost::shared_ptr<Texture1D> Texture1DSP;

#endif /* TEXTURE1D_H_ */
