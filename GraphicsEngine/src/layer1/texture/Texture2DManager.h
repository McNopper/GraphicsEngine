/*
 * Texture2DManager.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTURE2DMANAGER_H_
#define TEXTURE2DMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Texture2D.h"

class Texture2DManager : public Singleton<Texture2DManager>
{

	friend class Singleton<Texture2DManager>;

private:

	KeyValueMap<std::string, Texture2DSP> allTextures;

private:

	Texture2DManager();
	virtual ~Texture2DManager();

public:

	void addTexture(const std::string& key, const Texture2DSP& texture);

	Texture2DSP createTexture(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture2DSP createTexture(const std::string& key, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture2DSP createTexture(const std::string& key, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture2DSP createTexture(const std::string& key, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixels, std::uint32_t sizeOfData, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

};

#endif /* TEXTURE2DMANAGER_H_ */
