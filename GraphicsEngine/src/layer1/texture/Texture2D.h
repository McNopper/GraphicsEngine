/*
 * Texture2D.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include "PixelData.h"
#include "TextureStandard.h"

class Texture2D : public TextureStandard
{

private:

	PixelData pixelData;

public:

	Texture2D(const std::string& identifier, float red);
	Texture2D(const std::string& identifier, const Color& color);
	Texture2D(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixels, std::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~Texture2D();

	virtual bool init();

	virtual void freePixels();

	const PixelData& getPixelData() const;

};

typedef std::shared_ptr<Texture2D> Texture2DSP;

#endif /* TEXTURE2D_H_ */
