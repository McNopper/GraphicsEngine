/*
 * TextureFactory_GLUS.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory_GLUS.h"

using namespace std;

TextureFactory::TextureFactory() :
		TextureFactoryBase()
{
}

TextureFactory::~TextureFactory()
{
}

void TextureFactory::destroyTgaImages(GLUStgaimage* image, int32_t start, int32_t end) const
{
	for (int32_t i = start; i < end; i++)
	{
		glusImageDestroyTga(&image[i]);
	}
}

void TextureFactory::destroyHdrImages(GLUShdrimage* image, int32_t start, int32_t end) const
{
	for (int32_t i = start; i < end; i++)
	{
		glusImageDestroyHdr(&image[i]);
	}
}

int32_t TextureFactory::getNumberChannels(GLenum format) const
{
	if (format == GL_RGB)
	{
		return 3;
	}
	else if (format == GL_RGBA)
	{
		return 4;
	}

	return 1;
}

bool TextureFactory::isTgaFilename(const string& filename) const
{
	if (filename.length() <= 5)
	{
		return false;
	}

	string tempFilename = filename.substr(filename.length() - 4, 4);

	transform(tempFilename.begin(), tempFilename.end(), tempFilename.begin(), ::tolower);

	return tempFilename.compare(".tga") == 0;
}

bool TextureFactory::isHdrFilename(const string& filename) const
{
	if (filename.length() <= 5)
	{
		return false;
	}

	string tempFilename = filename.substr(filename.length() - 4, 4);

	transform(tempFilename.begin(), tempFilename.end(), tempFilename.begin(), ::tolower);

	return tempFilename.compare(".hdr") == 0;
}

bool TextureFactory::loadTgaImage(const string& filename, std::string& identifier, GLUStgaimage& image) const
{
	string strippedFilename = filename;

	GLint found;

	GLboolean success = glusImageLoadTga(strippedFilename.c_str(), &image);

	if (!success)
	{
		found = strippedFilename.find_last_of("/");

		if (found != -1)
		{
			strippedFilename = strippedFilename.substr(found + 1);

			success = glusImageLoadTga(strippedFilename.c_str(), &image);
		}
		else
		{
			found = strippedFilename.find_last_of("\\");

			if (found != -1)
			{
				strippedFilename = strippedFilename.substr(found + 1);

				success = glusImageLoadTga(strippedFilename.c_str(), &image);
			}
		}
	}

	if (success)
	{
		found = strippedFilename.find_last_of(".");

		if (found != -1)
		{
			identifier = strippedFilename.substr(0, found);
		}
		else
		{
			identifier = strippedFilename;
		}

		return true;
	}
	else
	{
		glusLogPrint(GLUS_LOG_ERROR, "Texture not found %s", strippedFilename.c_str());
	}

	return false;
}

bool TextureFactory::loadHdrImage(const string& filename, std::string& identifier, GLUShdrimage& image) const
{
	string strippedFilename = filename;

	GLint found;

	GLboolean success = glusImageLoadHdr(strippedFilename.c_str(), &image);

	if (!success)
	{
		found = strippedFilename.find_last_of("/");

		if (found != -1)
		{
			strippedFilename = strippedFilename.substr(found + 1);

			success = glusImageLoadHdr(strippedFilename.c_str(), &image);
		}
		else
		{
			found = strippedFilename.find_last_of("\\");

			if (found != -1)
			{
				strippedFilename = strippedFilename.substr(found + 1);

				success = glusImageLoadHdr(strippedFilename.c_str(), &image);
			}
		}
	}

	if (success)
	{
		found = strippedFilename.find_last_of(".");

		if (found != -1)
		{
			identifier = strippedFilename.substr(0, found);
		}
		else
		{
			identifier = strippedFilename;
		}

		return true;
	}
	else
	{
		glusLogPrint(GLUS_LOG_ERROR, "Texture not found %s", strippedFilename.c_str());
	}

	return false;
}

Texture2DSP TextureFactory::loadTexture2D(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	Texture2DSP texture2D;

	string identifier;

	GLUStgaimage tgaimage;
	GLUShdrimage hdrimage;

	if (isTgaFilename(filename))
	{
		if (!loadTgaImage(filename, identifier, tgaimage))
		{
			return texture2D;
		}

		glusLogPrint(GLUS_LOG_DEBUG, "Creating texture: %s", filename.c_str());

		texture2D = Texture2DSP(new Texture2D(identifier, gatherInternalFormat(tgaimage.format, GL_UNSIGNED_BYTE), tgaimage.width, image_tgaeight, tgaimage.format, GL_UNSIGNED_BYTE, tgaimage.data, sizeof(uint8_t) * getNumberChannels(tgaimage.format) * tgaimage.width * image_tgaeight, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		glusImageDestroyTga(&tgaimage);
	}
	else if (isHdrFilename(filename))
	{
		if (!loadHdrImage(filename, identifier, hdrimage))
		{
			return texture2D;
		}

		glusLogPrint(GLUS_LOG_DEBUG, "Creating texture: %s", filename.c_str());

		texture2D = Texture2DSP(new Texture2D(identifier, gatherInternalFormat(hdrimage.format, GL_FLOAT), hdrimage.width, image_hdreight, hdrimage.format, GL_FLOAT, (uint8_t*)hdrimage.data, sizeof(float) * getNumberChannels(hdrimage.format) * hdrimage.width * image_hdreight, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		glusImageDestroyHdr(&hdrimage);
	}
	else
	{
		glusLogPrint(GLUS_LOG_ERROR, "Unsupported Texture format %s", filename.c_str());

		return texture2D;
	}

	return texture2D;
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	TextureCubeMapSP textureCubeMap;

	GLUStgaimage tgaimage[6];
	GLUShdrimage hdrimage[6];

	bool isTga = false;
	bool currentIsTga = false;

	string dummy;

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

		if (isTgaFilename(filename))
		{
			if (cubeMapSide == GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				isTga = true;
				currentIsTga = true;
			}
			else
			{
				currentIsTga = true;
			}
		}
		else if (isHdrFilename(filename))
		{
			if (cubeMapSide == GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				isTga = false;
				currentIsTga = false;
			}
			else
			{
				currentIsTga = false;
			}
		}

		if (isTga != currentIsTga)
		{
			if (isTga)
			{
				destroyTgaImages(tgaimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X);
			}
			else
			{
				destroyHdrImages(hdrimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X);
			}

			glusLogPrint(GLUS_LOG_ERROR, "Mismatching Texture format %s", filename.c_str());

			return textureCubeMap;
		}

		if (isTga && !loadTgaImage(filename, dummy, tgaimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]))
		{
			destroyTgaImages(tgaimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X);

			return textureCubeMap;
		}
		else if (!loadHdrImage(filename, dummy, hdrimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]))
		{
			destroyHdrImages(hdrimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X);

			return textureCubeMap;
		}

		if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
		{
			if (isTga && (sizeof(uint8_t) * getNumberChannels(tgaimage[0].format) * tgaimage[0].width * tgaimage[0].height != sizeof(uint8_t) * getNumberChannels(tgaimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].format) * tgaimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].width * tgaimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].height))
			{
				destroyTgaImages(tgaimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1);

				return textureCubeMap;
			}
			else if ((sizeof(float) * getNumberChannels(hdrimage[0].format) * hdrimage[0].width * hdrimage[0].height != sizeof(float) * getNumberChannels(hdrimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].format) * hdrimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].width * hdrimage[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].height))
			{
				destroyHdrImages(hdrimage, 0, cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1);

				return textureCubeMap;
			}
		}
	}

	glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture: %s", identifier.c_str());

	if (isTga)
	{
		textureCubeMap = TextureCubeMapSP(new TextureCubeMap(identifier, gatherInternalFormat(tgaimage[0].format, GL_UNSIGNED_BYTE), tgaimage[0].width, tgaimage[0].height, tgaimage[0].format, GL_UNSIGNED_BYTE, tgaimage[0].data, tgaimage[1].data, tgaimage[2].data, tgaimage[3].data, tgaimage[4].data, tgaimage[5].data, sizeof(uint8_t) * getNumberChannels(tgaimage[0].format) * tgaimage[0].width * tgaimage[0].height, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		destroyTgaImages(tgaimage, 0, 6);
	}
	else
	{
		textureCubeMap = TextureCubeMapSP(new TextureCubeMap(identifier, gatherInternalFormat(hdrimage[0].format, GL_FLOAT), hdrimage[0].width, hdrimage[0].height, hdrimage[0].format, GL_FLOAT, (uint8_t*)hdrimage[0].data, (uint8_t*)hdrimage[1].data, (uint8_t*)hdrimage[2].data, (uint8_t*)hdrimage[3].data, (uint8_t*)hdrimage[4].data, (uint8_t*)hdrimage[5].data, sizeof(float) * getNumberChannels(hdrimage[0].format) * hdrimage[0].width * hdrimage[0].width, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		destroyHdrImages(hdrimage, 0, 6);
	}

	return textureCubeMap;
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	glusLogPrint(GLUS_LOG_ERROR, "Unsupported Texture format %s", filename.c_str());

	return TextureCubeMapSP();
}

TextureCubeMapArraySP TextureFactory::loadTextureCubeMapArray(const string& identifier, const string filename[], int32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	TextureCubeMapArraySP textureCubeMapArray;

	GLUStgaimage* tgaimage = nullptr;
	GLUShdrimage* hdrimage = nullptr;

	const uint8_t** pixelsPos;

	string dummy;

	bool isTga = isTgaFilename(filename[0]);

	if (isTga)
	{
		tgaimage = new GLUStgaimage[sizeOfArray * 6];

		if (!tgaimage)
		{
			return textureCubeMapArray;
		}
	}
	else
	{
		hdrimage = new GLUShdrimage[sizeOfArray * 6];

		if (!hdrimage)
		{
			return textureCubeMapArray;
		}
	}

	pixelsPos = new const uint8_t*[sizeOfArray * 6];

	if (!pixelsPos)
	{
		if (isTga)
		{
			delete[] tgaimage;
		}
		else
		{
			delete[] hdrimage;
		}

		return textureCubeMapArray;
	}

	for (int32_t i = 0; i < sizeOfArray; i++)
	{
		for (int32_t k = 0; k < 6; k++)
		{
			if (isTga && !loadTgaImage(filename[i * 6 + k], dummy, tgaimage[i * 6 + k]))
			{
				destroyTgaImages(tgaimage, 0, i * 6 + k);

				delete[] tgaimage;
				delete[] pixelsPos;

				return textureCubeMapArray;
			}
			else if (!loadHdrImage(filename[i * 6 + k], dummy, hdrimage[i * 6 + k]))
			{
				destroyHdrImages(hdrimage, 0, i * 6 + k);

				delete[] hdrimage;
				delete[] pixelsPos;

				return textureCubeMapArray;
			}


			if (k > 0)
			{
				if (isTga && (sizeof(uint8_t) * getNumberChannels(tgaimage[0].format) * tgaimage[0].width * tgaimage[0].height != sizeof(uint8_t) * getNumberChannels(tgaimage[i * 6 + k].format) * tgaimage[i * 6 + k].width * tgaimage[i * 6 + k].height))
				{
					destroyTgaImages(tgaimage, 0, i * 6 + k + 1);

					delete[] tgaimage;
					delete[] pixelsPos;

					return textureCubeMapArray;
				}
				else if ((sizeof(float) * getNumberChannels(hdrimage[0].format) * hdrimage[0].width * hdrimage[0].height != sizeof(float) * getNumberChannels(hdrimage[i * 6 + k].format) * hdrimage[i * 6 + k].width * hdrimage[i * 6 + k].height))
				{
					destroyHdrImages(hdrimage, 0, i * 6 + k + 1);

					delete[] hdrimage;
					delete[] pixelsPos;

					return textureCubeMapArray;
				}
			}

			if (isTga)
			{
				pixelsPos[i * 6 + k] = tgaimage[i * 6 + k].data;
			}
			else
			{
				pixelsPos[i * 6 + k] = (uint8_t*)hdrimage[i * 6 + k].data;
			}
		}
	}

	glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture array: %s", identifier.c_str());

	if (isTga)
	{
		textureCubeMapArray = TextureCubeMapArraySP(new TextureCubeMapArray(identifier, gatherInternalFormat(tgaimage[0].format, GL_UNSIGNED_BYTE), tgaimage[0].width, tgaimage[0].height, tgaimage[0].format, GL_UNSIGNED_BYTE, pixelsPos, sizeof(uint8_t) * getNumberChannels(tgaimage[0].format) * tgaimage[0].width * tgaimage[0].height, sizeOfArray, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		destroyTgaImages(tgaimage, 0, sizeOfArray * 6);

		delete[] tgaimage;
	}
	else
	{
		textureCubeMapArray = TextureCubeMapArraySP(new TextureCubeMapArray(identifier, gatherInternalFormat(hdrimage[0].format, GL_FLOAT), hdrimage[0].width, hdrimage[0].height, hdrimage[0].format, GL_FLOAT, pixelsPos, sizeof(float) * getNumberChannels(hdrimage[0].format) * hdrimage[0].width * hdrimage[0].height, sizeOfArray, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		destroyHdrImages(hdrimage, 0, sizeOfArray * 6);

		delete[] hdrimage;
	}

	delete[] pixelsPos;

	return textureCubeMapArray;
}

//
// Saving
//

bool TextureFactory::saveImage(const string& identifier, const PixelData& pixelData) const
{
	GLboolean result;

	if (pixelData.getType() == GL_FLOAT || pixelData.getType() == GL_HALF_FLOAT)
	{
		GLUShdrimage hdrimage;

		string filename = identifier + ".hdr";

		hdrimage.width = pixelData.getWidth();
		image_hdreight = pixelData.getHeight();
		hdrimage.depth= 1;
		hdrimage.format = pixelData.getFormat();
		hdrimage.data = (float*)pixelData.getPixels();

		glusLogPrint(GLUS_LOG_DEBUG, "Saving HDR texture: %s", filename.c_str());

		result = glusImageSaveHdr(filename.c_str(), &hdrimage);
	}
	else
	{
		GLUStgaimage tgaimage;

		string filename = identifier + ".tga";

		tgaimage.width = pixelData.getWidth();
		image_tgaeight = pixelData.getHeight();
		tgaimage.depth= 1;
		tgaimage.format = pixelData.getFormat();
		tgaimage.data = pixelData.getPixels();

		glusLogPrint(GLUS_LOG_DEBUG, "Saving TGA texture: %s", filename.c_str());

		result = glusImageSaveTga(filename.c_str(), &tgaimage);
	}

	return static_cast<bool>(result == GL_TRUE);
}
