/*
 * Texture2DManager.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory.h"

#include "Texture2DManager.h"

using namespace std;

Texture2DManager::Texture2DManager() :
		Singleton<Texture2DManager>(), allTextures()
{
}

Texture2DManager::~Texture2DManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

void Texture2DManager::addTexture(const string& key, const Texture2DSP& texture)
{
	allTextures[key] = texture;
}

Texture2DSP Texture2DManager::createTexture(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(filename))
	{
		allTextures[filename] = textureFactory.loadTexture2D(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[filename];
	}

	return allTextures[filename];
}

Texture2DSP Texture2DManager::createTexture(const string& key, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture2DSP Texture2DManager::createTexture(const string& key, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture2DSP Texture2DManager::createTexture(const string& key, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, internalFormat, width, height, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}
