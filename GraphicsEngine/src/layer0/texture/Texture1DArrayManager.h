/*
 * Texture1DArrayManager.h
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#ifndef TEXTURE1DARRAYMANAGER_H_
#define TEXTURE1DARRAYMANAGER_H_

#include "../../UsedLibs.h"

#include "Texture1DArray.h"

class Texture1DArrayManager
{
private:

	static Texture1DArrayManager* instance;

	std::map<std::string, Texture1DArraySP> allTextures;

private:

	Texture1DArrayManager();
	virtual ~Texture1DArrayManager();

public:

	static Texture1DArrayManager* getInstance();

	static void terminate();

	void addTexture(const std::string& key, const Texture1DArraySP& texture);

	Texture1DArraySP createTexture(const std::string& key, boost::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE);

	Texture1DArraySP createTexture(const std::string& key, GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE);

};

#endif /* TEXTURE1DARRAYMANAGER_H_ */
