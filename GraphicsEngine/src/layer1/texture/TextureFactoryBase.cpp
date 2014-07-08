/*
 * TextureFactory.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactoryBase.h"

using namespace std;

TextureFactoryBase::TextureFactoryBase() :
		autoInternalFloat(false), autoInternalInteger(true), floatBitsPerPixel(BitsPerPixel16), integerBitsPerPixel(BitsPerPixel8)
{
}

TextureFactoryBase::~TextureFactoryBase()
{
}

GLenum TextureFactoryBase::gatherInternalFormat(GLenum format, GLenum type) const
{
	if (type == GL_FLOAT || type == GL_HALF_FLOAT)
	{
		if (autoInternalFloat)
		{
			return format;
		}

		if (format == GL_RGB)
		{
			switch (floatBitsPerPixel)
			{
				case BitsPerPixel8:
					glusLogPrint(GLUS_LOG_WARNING, "No 8 bit floating point internal format. Using automatic format.");
				break;
				case BitsPerPixel16:
					return GL_RGB16F;
				break;
				case BitsPerPixel32:
					return GL_RGB32F;
				break;
			}

			return GL_RGB;
		}
		else if (format == GL_RGBA)
		{
			switch (floatBitsPerPixel)
			{
				case BitsPerPixel8:
					glusLogPrint(GLUS_LOG_WARNING, "No 8 bit floating point internal format. Using automatic format.");
				break;
				case BitsPerPixel16:
					return GL_RGBA16F;
				break;
				case BitsPerPixel32:
					return GL_RGBA32F;
				break;
			}

			return GL_RGBA;
		}

		return format;
	}

	if (autoInternalInteger)
	{
		return format;
	}

	if (format == GL_RGB)
	{
		switch (integerBitsPerPixel)
		{
			case BitsPerPixel8:
				return GL_RGB8;
			break;
			case BitsPerPixel16:
				return GL_RGB16;
			break;
			case BitsPerPixel32:
				if (type == GL_BYTE || type == GL_SHORT || type == GL_INT)
				{
					return GL_RGB32I;
				}
				else
				{
					return GL_RGB32UI;
				}
			break;
		}

		return GL_RGB;
	}
	else if (format == GL_RGBA)
	{
		switch (integerBitsPerPixel)
		{
			case BitsPerPixel8:
				return GL_RGBA8;
			break;
			case BitsPerPixel16:
				return GL_RGBA16;
			break;
			case BitsPerPixel32:
				if (type == GL_BYTE || type == GL_SHORT || type == GL_INT)
				{
					return GL_RGBA32I;
				}
				else
				{
					return GL_RGBA32UI;
				}
			break;
		}

		return GL_RGBA;
	}

	return format;
}

Texture1DSP TextureFactoryBase::createTexture1D(const string& identifier, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture1DSP(new Texture1D(identifier, gatherInternalFormat(format, type), width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture1DSP TextureFactoryBase::createTexture1D(const string& identifier, GLint internalFormat, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture1DSP(new Texture1D(identifier, internalFormat, width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture1DArraySP TextureFactoryBase::createTexture1DArray(const string& identifier, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture1DArraySP(new Texture1DArray(identifier, gatherInternalFormat(format, type), width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture1DArraySP TextureFactoryBase::createTexture1DArray(const string& identifier, int internalFormat, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture1DArraySP(new Texture1DArray(identifier, internalFormat, width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DSP TextureFactoryBase::createTexture2D(const string& identifier, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture2DSP(new Texture2D(identifier, gatherInternalFormat(format, type), width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DSP TextureFactoryBase::createTexture2D(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture2DSP(new Texture2D(identifier, internalFormat, width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DSP TextureFactoryBase::createTexture2D(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture2DSP(new Texture2D(identifier, internalFormat, width, height, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DArraySP TextureFactoryBase::createTexture2DArray(const string& identifier, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture2DArraySP(new Texture2DArray(identifier, gatherInternalFormat(format, type), width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DArraySP TextureFactoryBase::createTexture2DArray(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Texture2DArraySP(new Texture2DArray(identifier, internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Texture2DMultisampleSP TextureFactoryBase::createTexture2DMultisample(const string& identifier, int32_t samples, GLint internalFormat, int32_t width, int32_t height, bool fixedsamplelocations) const
{
	return Texture2DMultisampleSP(new Texture2DMultisample(identifier, samples, internalFormat, width, height, fixedsamplelocations));
}

TextureCubeMapSP TextureFactoryBase::createTextureCubeMap(const string& identifier, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return TextureCubeMapSP(new TextureCubeMap(identifier, gatherInternalFormat(format, type), width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

TextureCubeMapSP TextureFactoryBase::createTextureCubeMap(const string& identifier, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return TextureCubeMapSP(new TextureCubeMap(identifier, internalFormat, width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

bool TextureFactoryBase::isAutoInternalFloat() const
{
	return autoInternalFloat;
}

void TextureFactoryBase::setAutoInternalFloat(bool autoInternalFloat)
{
	this->autoInternalFloat = autoInternalFloat;
}

bool TextureFactoryBase::isAutoInternalInteger() const
{
	return autoInternalInteger;
}

void TextureFactoryBase::setAutoInternalInteger(bool autoInternalInteger)
{
	this->autoInternalInteger = autoInternalInteger;
}

enum FormatDepth TextureFactoryBase::getFloatBitsPerPixel() const
{
	return floatBitsPerPixel;
}

void TextureFactoryBase::setFloatBitsPerPixel(enum FormatDepth floatBitsPerPixel)
{
	this->floatBitsPerPixel = floatBitsPerPixel;
}

enum FormatDepth TextureFactoryBase::getIntegerBitsPerPixel() const
{
	return integerBitsPerPixel;
}

void TextureFactoryBase::setIntegerBitsPerPixel(enum FormatDepth integerBitsPerPixel)
{
	this->integerBitsPerPixel = integerBitsPerPixel;
}

//
// Saving
//

bool TextureFactoryBase::saveTexture2D(const Texture2DSP texture2D) const
{
	return saveTexture2D(texture2D, "");
}

bool TextureFactoryBase::saveTextureCubeMap(const TextureCubeMapSP textureCubeMap) const
{
	return saveTextureCubeMap(textureCubeMap, "");
}

bool TextureFactoryBase::saveTexture2D(const Texture2DSP texture2D, const string& path) const
{
	return saveImage(path + texture2D->getIdentifier(), texture2D->getPixelData());
}

bool TextureFactoryBase::saveTextureCubeMap(const TextureCubeMapSP textureCubeMap, const string& path) const
{
	string postFix;

	for (int32_t i = 0; i < 6; i++)
	{
		switch (i)
		{
			case 0:
				postFix = "_posX";
			break;
			case 1:
				postFix = "_negX";
			break;
			case 2:
				postFix = "_posY";
			break;
			case 3:
				postFix = "_negY";
			break;
			case 4:
				postFix = "_posZ";
			break;
			case 5:
				postFix = "_negZ";
			break;
		}

		saveImage(path + textureCubeMap->getIdentifier() + postFix, textureCubeMap->getPixelData(i));
	}

	return true;
}
