/*
 * Texture1DArrayManager.h
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#ifndef TEXTURE1DARRAYMANAGER_H_
#define TEXTURE1DARRAYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Texture1DArray.h"

class Texture1DArrayManager : public Singleton<Texture1DArrayManager>
{

	friend class Singleton<Texture1DArrayManager>;

private:

	KeyValueMap<std::string, Texture1DArraySP> allTextures;

private:

	Texture1DArrayManager();
	virtual ~Texture1DArrayManager();

public:

	void addTexture(const std::string& key, const Texture1DArraySP& texture);

	Texture1DArraySP createTexture(const std::string& key, std::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT);

	Texture1DArraySP createTexture(const std::string& key, GLint internalFormat, std::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT);

};

#endif /* TEXTURE1DARRAYMANAGER_H_ */
