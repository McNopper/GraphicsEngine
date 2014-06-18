/*
 * TextureFactory_DevIL.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory_DevIL.h"

using namespace std;

TextureFactory::TextureFactory() :
		TextureFactoryBase()
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

ILuint TextureFactory::loadImage(const string& filename, string& identifier) const
{
	ILuint imageName = 0;

	string strippedFilename = filename;

	ILint found;

	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	ILboolean success = ilLoadImage((const ILstring)strippedFilename.c_str());

	if (!success)
	{
		found = strippedFilename.find_last_of("/");

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

		if (imageInfo.Type != IL_FLOAT && imageInfo.Type != IL_UNSIGNED_BYTE)
		{
			if (imageInfo.Type == IL_DOUBLE || imageInfo.Type == IL_HALF)
			{
				ilConvertImage(imageInfo.Format, IL_FLOAT);
			}
			else
			{
				ilConvertImage(imageInfo.Format, IL_UNSIGNED_BYTE);
			}
		}

		if (imageInfo.Format == IL_BGR)
		{
			ilConvertImage(IL_RGB, imageInfo.Type);
		}
		else if (imageInfo.Format == IL_BGRA)
		{
			ilConvertImage(IL_RGBA, imageInfo.Type);
		}

		found = strippedFilename.find_last_of(".");

		if (found != -1)
		{
			identifier = strippedFilename.substr(0, found);
		}
		else
		{
			identifier = strippedFilename;
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

Texture2DSP TextureFactory::loadTexture2D(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	Texture2DSP texture2D;

	string identifier;

	ILuint imageName = loadImage(filename, identifier);

	if (imageName)
	{
		ILinfo imageInfo;

		iluGetImageInfo(&imageInfo);

		glusLogPrint(GLUS_LOG_DEBUG, "Creating texture: %s", filename.c_str());

		texture2D = Texture2DSP(new Texture2D(identifier, gatherInternalFormat(imageInfo.Format, imageInfo.Type), imageInfo.Width, imageInfo.Height, imageInfo.Format, imageInfo.Type, imageInfo.Data, imageInfo.SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		ilBindImage(0);
		ilDeleteImages(1, &imageName);
	}

	return texture2D;
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	TextureCubeMapSP textureCubeMap;

	ILuint imageName[6];
	ILinfo imageInfo[6];

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

		imageName[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X] = loadImage(filename, dummy);

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

	glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture: %s", identifier.c_str());

	textureCubeMap = TextureCubeMapSP(new TextureCubeMap(identifier, gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

	ilBindImage(0);
	ilDeleteImages(6, imageName);

	return textureCubeMap;
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	TextureCubeMapSP textureCubeMap;

	ILinfo imageInfo[6];

	string identifier;

	ILuint imageName = loadImage(filename, identifier);

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

		glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture: %s", identifier.c_str());

		textureCubeMap = TextureCubeMapSP(new TextureCubeMap(identifier, gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		ilBindImage(0);
		ilDeleteImages(1, &imageName);
	}

	return textureCubeMap;
}

TextureCubeMapArraySP TextureFactory::loadTextureCubeMapArray(const string& identifier, const string filename[], int32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	TextureCubeMapArraySP textureCubeMapArray;

	ILuint* imageName;
	ILinfo* imageInfo;

	const uint8_t** pixelsPos;

	string dummy;

	imageName = new ILuint[sizeOfArray * 6];

	if (!imageName)
	{
		return textureCubeMapArray;
	}

	imageInfo = new ILinfo[sizeOfArray * 6];

	if (!imageInfo)
	{
		delete[] imageName;

		return textureCubeMapArray;
	}

	pixelsPos = new const uint8_t*[sizeOfArray * 6];

	if (!pixelsPos)
	{
		delete[] imageName;
		delete[] imageInfo;

		return textureCubeMapArray;
	}

	for (int32_t i = 0; i < sizeOfArray; i++)
	{
		for (int32_t k = 0; k < 6; k++)
		{
			imageName[i * 6 + k] = loadImage(filename[i * 6 + k], dummy);

			if (imageName[i * 6 + k])
			{
				iluGetImageInfo(&imageInfo[i * 6 + k]);

				if (k > 0)
				{
					if (imageInfo[6 * sizeOfArray].SizeOfData != imageInfo[6 * sizeOfArray - 1].SizeOfData)
					{
						ilBindImage(0);
						ilDeleteImages(6 * sizeOfArray, imageName);

						delete[] imageName;
						delete[] imageInfo;
						delete[] pixelsPos;

						return textureCubeMapArray;
					}
				}
			}
			else
			{
				if (k > 0)
				{
					ilBindImage(0);
					ilDeleteImages(6 * sizeOfArray, imageName);
				}

				delete[] imageName;
				delete[] imageInfo;
				delete[] pixelsPos;

				return textureCubeMapArray;
			}

			pixelsPos[i * 6 + k] = imageInfo[i * 6 + k].Data;
		}

	}

	glusLogPrint(GLUS_LOG_DEBUG, "Creating cube texture array: %s", identifier.c_str());

	textureCubeMapArray = TextureCubeMapArraySP(new TextureCubeMapArray(identifier, gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, pixelsPos, imageInfo[0].SizeOfData, sizeOfArray, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

	ilBindImage(0);
	ilDeleteImages(6 * sizeOfArray, imageName);

	delete[] imageName;
	delete[] imageInfo;
	delete[] pixelsPos;

	return textureCubeMapArray;
}

//
// Saving
//

bool TextureFactory::saveImage(const string& identifier, const PixelData& pixelData) const
{
	ILuint imageName = 0;
	ILboolean result;
	ILubyte numChannels = 1;

	if (pixelData.getFormat() == GL_RGB)
	{
		numChannels = 3;
	}
	else if (pixelData.getFormat() == GL_RGBA)
	{
		numChannels = 4;
	}

	// If HDR format, force to three channels.
	if (pixelData.getType() == GL_FLOAT || pixelData.getType() == GL_HALF_FLOAT)
	{
		numChannels = 3;
	}

	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	// Format and type should match OpenGL
	ilTexImage(pixelData.getWidth(), pixelData.getHeight(), 0, numChannels, pixelData.getFormat(), pixelData.getType(), pixelData.getPixels());

	ilEnable(IL_FILE_OVERWRITE);

	if (pixelData.getType() == GL_FLOAT || pixelData.getType() == GL_HALF_FLOAT)
	{
		string filename = identifier + ".hdr";

		glusLogPrint(GLUS_LOG_DEBUG, "Saving HDR texture: %s", filename.c_str());

		result = ilSave(IL_HDR, filename.c_str());
	}
	else
	{
		string filename = identifier + ".tga";

		glusLogPrint(GLUS_LOG_DEBUG, "Saving TGA texture: %s", filename.c_str());

		result = ilSave(IL_TGA, filename.c_str());
	}

	ilBindImage(0);
	ilDeleteImages(1, &imageName);

	return static_cast<bool>(result == IL_TRUE);
}
