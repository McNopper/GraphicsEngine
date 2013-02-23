/*
 * TextureStandard.h
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#ifndef TEXTURESTANDARD_H_
#define TEXTURESTANDARD_H_

#include "Texture.h"

class TextureStandard : public Texture
{

protected:

	GLenum format;
	GLenum type;

	boost::uint32_t sizeOfData;

	bool mipMap;

	GLint minFilter;
	GLint magFilter;
	GLint wrapS;
	GLint wrapT;

	virtual void changingSize();

public:
	TextureStandard(GLenum target, GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, boost::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
	virtual ~TextureStandard();

	virtual void freePixels() = 0;

	bool isMipMap() const;
	void setMipMap(bool mipMap);

	GLint getMinFilter() const;
	void setMinFilter(GLint minFilter);

	GLint getMagFilter() const;
	void setMagFilter(GLint magFilter);

	GLint getWrapS() const;
	void setWrapS(GLint wrapS);

	GLint getWrapT() const;
	void setWrapT(GLint wrapT);

};

#endif /* TEXTURESTANDARD_H_ */
