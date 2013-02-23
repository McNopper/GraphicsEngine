/*
 * TextureFactory.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include <IL/il.h>
#include <IL/ilu.h>

#include "TextureFactory.h"

using namespace std;
using namespace boost;

TextureFactory::TextureFactory() : autoInternalFloat(false), autoInternalInteger(true), floatBitsPerPixel(BitsPerPixel16), integerBitsPerPixel(BitsPerPixel8)
{
	ilInit();
	iluInit();

	ilEnable(IL_CONV_PAL);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
}

TextureFactory::~TextureFactory()
{
}

GLuint TextureFactory::loadImage(const string& filename) const
{
	ILuint imageName = 0;

	string strippedFilename = filename;

	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	ILboolean success = ilLoadImage((const ILstring)strippedFilename.c_str());

	if (!success)
	{
		ILint found = strippedFilename.find_last_of("/");

		if (found != -1)
		{
			strippedFilename = strippedFilename.substr(found + 1);

			success = ilLoadImage((const ILstring)strippedFilename.c_str());
		}
		else
		{
			found = strippedFilename.find_last_of("\\");

			if (found != -1)
			{
				strippedFilename = strippedFilename.substr(found + 1);

				success = ilLoadImage((const ILstring)strippedFilename.c_str());
			}
		}
	}

	if (success)
	{
		ILinfo imageInfo;

		iluGetImageInfo(&imageInfo);

		if (imageInfo.Format == IL_BGR)
		{
			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		}
		else if (imageInfo.Format == IL_BGRA)
		{
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		}

		return imageName;
	}
	else
	{
		ilBindImage(0);
		ilDeleteImages(1, &imageName);

		glusLogPrint(GLUS_LOG_ERROR, "Texture not found %s", strippedFilename.c_str());
	}

	return 0;
}

GLenum TextureFactory::gatherInternalFormat(GLenum format, GLenum type) const
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

Texture1DSP TextureFactory::createTexture1D(int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return Texture1DSP(new Texture1D(gatherInternalFormat(format, type), width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT));
}

Texture1DSP TextureFactory::createTexture1D(GLint internalFormat, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return Texture1DSP(new Texture1D(internalFormat, width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT));
}

Texture2DSP TextureFactory::createTexture2D(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	Texture2DSP texture2D;

	ILuint imageName  = loadImage(filename);

	if (imageName)
	{
		ILinfo imageInfo;

		iluGetImageInfo(&imageInfo);

		glusLogPrint(GLUS_LOG_DEBUG, "Creating texture: %s", filename.c_str());

		texture2D = Texture2DSP(new Texture2D(gatherInternalFormat(imageInfo.Format, imageInfo.Type), imageInfo.Width, imageInfo.Height, imageInfo.Format, imageInfo.Type, imageInfo.Data, imageInfo.SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT));

		ilBindImage(0);
		ilDeleteImages(1, &imageName);
	}

	return texture2D;
}

Texture2DSP TextureFactory::createTexture2D(int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return Texture2DSP(new Texture2D(gatherInternalFormat(format, type), width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT));
}

Texture2DSP TextureFactory::createTexture2D(GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return Texture2DSP(new Texture2D(internalFormat, width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT));
}

Texture2DMultisampleSP TextureFactory::createTexture2DMultisample(int32_t samples, GLint internalFormat, int32_t width, int32_t height, bool fixedsamplelocations) const
{
	return Texture2DMultisampleSP(new Texture2DMultisample(samples, internalFormat, width, height, fixedsamplelocations));
}

TextureCubeMapSP TextureFactory::createTextureCubeMap(const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	TextureCubeMapSP textureCubeMap;

	ILuint imageName[6];
	ILinfo imageInfo[6];

	for (GLenum cubeMapSide = GL_TEXTURE_CUBE_MAP_POSITIVE_X; cubeMapSide <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; cubeMapSide++)
	{
		string filename;

		switch (cubeMapSide)
		{
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
				filename = posX;
			break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
				filename = negX;
			break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
				filename = posY;
			break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
				filename = negY;
			break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
				filename = posZ;
			break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
				filename = negZ;
			break;
		}

		imageName[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X] = loadImage(filename);

		if (imageName[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X])
		{
			iluGetImageInfo(&imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]);

			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				if (imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData != imageInfo[cubeMapSide - 1 - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData)
				{
					ilBindImage(0);
					ilDeleteImages(cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X, imageName);

					return textureCubeMap;
				}
			}
		}
		else
		{
			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				ilBindImage(0);
				ilDeleteImages(cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X, imageName);
			}

			return textureCubeMap;
		}
	}

	glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture: %s", posX.c_str());

	textureCubeMap = TextureCubeMapSP(new TextureCubeMap(gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT));

	ilBindImage(0);
	ilDeleteImages(6, imageName);

	return textureCubeMap;
}

TextureCubeMapSP TextureFactory::createTextureCubeMap(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	TextureCubeMapSP textureCubeMap;

	ILinfo imageInfo[6];

	ILuint imageName = loadImage(filename);

	if (imageName)
	{
		GLint activeFace = 0;

		for (GLenum cubeMapSide = GL_TEXTURE_CUBE_MAP_POSITIVE_X; cubeMapSide <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; cubeMapSide++)
		{
			ilBindImage(imageName);

			ilActiveFace(activeFace);

			// This avoids modifying the faces on the y-axes
			if (activeFace < 2 || activeFace > 3)
			{
				iluMirror();
				iluFlipImage();
			}

			iluGetImageInfo(&imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]);

			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				if (imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData != imageInfo[cubeMapSide - 1 - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData)
				{
					ilBindImage(0);
					ilDeleteImages(1, &imageName);

					return textureCubeMap;
				}
			}

			activeFace++;

			// This switches the faces for the z-axes
			if (activeFace == 4)
			{
				activeFace = 5;
			}
			else if (activeFace == 5)
			{
				activeFace = 6;
			}
			else if (activeFace == 6)
			{
				activeFace = 4;
			}
		}

		glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture: %s", filename.c_str());

		textureCubeMap = TextureCubeMapSP(new TextureCubeMap(gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT));

		ilBindImage(0);
		ilDeleteImages(1, &imageName);
	}

	return textureCubeMap;
}

TextureCubeMapSP TextureFactory::createTextureCubeMap(int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return TextureCubeMapSP(new TextureCubeMap(gatherInternalFormat(format, type), width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT));
}

TextureCubeMapSP TextureFactory::createTextureCubeMap(GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) const
{
	return TextureCubeMapSP(new TextureCubeMap(internalFormat, width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT));
}


bool TextureFactory::isAutoInternalFloat() const
{
	return autoInternalFloat;
}

void TextureFactory::setAutoInternalFloat(bool autoInternalFloat)
{
	this->autoInternalFloat = autoInternalFloat;
}

bool TextureFactory::isAutoInternalInteger() const
{
	return autoInternalInteger;
}

void TextureFactory::setAutoInternalInteger(bool autoInternalInteger)
{
	this->autoInternalInteger = autoInternalInteger;
}

enum FormatDepth TextureFactory::getFloatBitsPerPixel() const
{
	return floatBitsPerPixel;
}

void TextureFactory::setFloatBitsPerPixel(enum FormatDepth floatBitsPerPixel)
{
	this->floatBitsPerPixel = floatBitsPerPixel;
}

enum FormatDepth TextureFactory::getIntegerBitsPerPixel() const
{
	return integerBitsPerPixel;
}

void TextureFactory::setIntegerBitsPerPixel(enum FormatDepth integerBitsPerPixel)
{
	this->integerBitsPerPixel = integerBitsPerPixel;
}
