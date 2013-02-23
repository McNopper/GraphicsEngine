/*
 * Texture2D.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include "TextureStandard.h"

class Texture2D : public TextureStandard
{

private:

	boost::uint8_t* pixels;

public:

	Texture2D(GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, const boost::uint8_t* pixels, boost::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
	virtual ~Texture2D();

	virtual bool init();

	virtual void freePixels();

};

typedef boost::shared_ptr<Texture2D> Texture2DSP;

#endif /* TEXTURE2D_H_ */
