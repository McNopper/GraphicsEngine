/*
 * Texture2DManager.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTURE2DMANAGER_H_
#define TEXTURE2DMANAGER_H_

#include "../../UsedLibs.h"

#include "Texture2D.h"

class Texture2DManager
{

private:

	static Texture2DManager* instance;

	std::map<std::string, Texture2DSP> allTextures;

private:

	Texture2DManager();
	virtual ~Texture2DManager();

public:

	static Texture2DManager* getInstance();

	static void terminate();

	void addTexture(const std::string& key, const Texture2DSP& texture);

	Texture2DSP createTexture(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture2DSP createTexture(const std::string& key, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

	Texture2DSP createTexture(const std::string& key, GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);

};

#endif /* TEXTURE2DMANAGER_H_ */
