/*
 * TextureStandard.h
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#ifndef TEXTURESTANDARD_H_
#define TEXTURESTANDARD_H_

#include "../../layer0/color/Color.h"

#include "Texture.h"

class TextureStandard : public Texture
{

protected:

	GLenum format;
	GLenum type;

	std::uint32_t sizeOfData;

	bool mipMap;

	GLint minFilter;
	GLint magFilter;
	GLint wrapS;
	GLint wrapT;

	float anisotropic;
	bool hasAnisotropic;

	virtual void changingSize();

public:
	TextureStandard(const std::string& identifier, GLenum target, float red);
	TextureStandard(const std::string& identifier, GLenum target, const Color& color);
	TextureStandard(const std::string& identifier, GLenum target, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, std::uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
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

	float getAnisotropic() const;
	void setAnisotropic(float level);
	void setMaxAnisotropic();

	GLenum getFormat() const;
	GLenum getType() const;
};

#endif /* TEXTURESTANDARD_H_ */
