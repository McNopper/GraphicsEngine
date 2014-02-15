/*
 * Texture1DManager.cpp
 *
 *  Created on: 20.12.2012
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture1DManager.h"

using namespace std;
using namespace boost;

Texture1DManager* Texture1DManager::instance;

Texture1DManager::Texture1DManager() :
	allTextures()
{
}

Texture1DManager::~Texture1DManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

Texture1DManager* Texture1DManager::getInstance()
{
	if (!instance)
	{
		instance = new Texture1DManager();
	}

	return instance;
}

void Texture1DManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void Texture1DManager::addTexture(const string& key, const Texture1DSP& texture)
{
	allTextures[key] = texture;
}

Texture1DSP Texture1DManager::createTexture(const string& key, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture1D(key, width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture1DSP Texture1DManager::createTexture(const string& key, GLint internalFormat, int32_t width, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture1D(key, internalFormat, width, format, type, pixels, sizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}


