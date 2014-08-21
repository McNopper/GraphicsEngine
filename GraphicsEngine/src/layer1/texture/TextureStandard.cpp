/*
 * TextureStandard.cpp
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#include "TextureStandard.h"

using namespace std;

TextureStandard::TextureStandard(const std::string& identifier, GLenum target, float red) :
		Texture(identifier, target, GL_R32F, 1, 1),
		format(GL_RED), type(GL_FLOAT), sizeOfData(sizeof(red)), mipMap(false), minFilter(GL_NEAREST), magFilter(GL_NEAREST), wrapS(GL_REPEAT), wrapT(GL_REPEAT), anisotropic(1.0)
{
	hasAnisotropic = glusExtensionIsSupported("GL_EXT_texture_filter_anisotropic") ? true : false;

	setAnisotropic(false);
}

TextureStandard::TextureStandard(const string& identifier, GLenum target, const Color& color) :
		Texture(identifier, target, GL_RGBA32F, 1, 1),
		format(GL_RGBA), type(GL_FLOAT), sizeOfData(sizeof(color)), mipMap(false), minFilter(GL_NEAREST), magFilter(GL_NEAREST), wrapS(GL_REPEAT), wrapT(GL_REPEAT), anisotropic(1.0)
{
	hasAnisotropic = glusExtensionIsSupported("GL_EXT_texture_filter_anisotropic") ? true : false;

	setAnisotropic(false);
}

TextureStandard::TextureStandard(const string& identifier, GLenum target, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
		Texture(identifier, target, internalFormat, width, height),
		format(format), type(type), sizeOfData(sizeOfData), mipMap(mipMap), minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT), anisotropic(1.0)
{
	hasAnisotropic = glusExtensionIsSupported("GL_EXT_texture_filter_anisotropic") ? true : false;

	setAnisotropic(anisotropic);
}

TextureStandard::~TextureStandard()
{
}

void TextureStandard::changingSize()
{
	freePixels();
}

bool TextureStandard::isMipMap() const
{
	return mipMap;
}

void TextureStandard::setMipMap(bool mipMap)
{
	if (this->mipMap != mipMap)
	{
		destroy();

		this->mipMap = mipMap;

		init();
	}
}

GLint TextureStandard::getMinFilter() const
{
	return minFilter;
}

void TextureStandard::setMinFilter(GLint minFilter)
{
	if (this->minFilter != minFilter)
	{
		this->minFilter = minFilter;

		glBindTexture(target, textureName);

		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	}
}

GLint TextureStandard::getMagFilter() const
{
	return magFilter;
}

void TextureStandard::setMagFilter(GLint magFilter)
{
	if (this->magFilter != magFilter)
	{
		this->magFilter = magFilter;

		glBindTexture(target, textureName);

		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	}
}

GLint TextureStandard::getWrapS() const
{
	return wrapS;
}

void TextureStandard::setWrapS(GLint wrapS)
{
	if (this->wrapS != wrapS)
	{
		this->wrapS = wrapS;

		glBindTexture(target, textureName);

		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
	}
}

GLint TextureStandard::getWrapT() const
{
	return wrapT;
}

void TextureStandard::setWrapT(GLint wrapT)
{
	if (this->wrapT != wrapT)
	{
		this->wrapT = wrapT;

		glBindTexture(target, textureName);

		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
	}
}

float TextureStandard::getAnisotropic() const
{
	return anisotropic;
}

void TextureStandard::setAnisotropic(float level)
{
	if (hasAnisotropic)
	{
		float max = 1.0f;

		if (level < 1.0f)
		{
			level = 1.0;
		}

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);

		if (level > max)
		{
			level = max;
		}

		glBindTexture(target, textureName);

		glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, level);
	}
}

void TextureStandard::setMaxAnisotropic()
{
	if (hasAnisotropic)
	{
		float max = 1.0f;

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);

		setAnisotropic(max);
	}
}

GLenum TextureStandard::getFormat() const
{
	return format;
}

GLenum TextureStandard::getType() const
{
	return type;
}
