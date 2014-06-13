/*
 * Texture1DManager.h
 *
 *  Created on: 20.12.2012
 *      Author: nopper
 */

#ifndef TEXTURE1DMANAGER_H_
#define TEXTURE1DMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Texture1D.h"

class Texture1DManager : public Singleton<Texture1DManager>
{

	friend class Singleton<Texture1DManager>;

private:

	KeyValueMap<std::string, Texture1DSP> allTextures;

private:

	Texture1DManager();
	virtual ~Texture1DManager();

public:

	void addTexture(const std::string& key, const Texture1DSP& texture);

	Texture1DSP createTexture(const std::string& key, std::int32_t width, GLenum format, GLenum type, const std::uint8_t* pixels = nullptr, std::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture1DSP createTexture(const std::string& key, GLint internalFormat, std::int32_t width, GLenum format, GLenum type, const std::uint8_t* pixels = nullptr, std::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

};

#endif /* TEXTURE1DMANAGER_H_ */
