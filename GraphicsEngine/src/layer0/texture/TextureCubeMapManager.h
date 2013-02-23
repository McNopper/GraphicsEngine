/*
 * TextureCubeMapManager.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTURECUBEMAPMANAGER_H_
#define TEXTURECUBEMAPMANAGER_H_

#include "../../UsedLibs.h"

#include "TextureCubeMap.h"

class TextureCubeMapManager
{

private:

	static TextureCubeMapManager* instance;

	std::map<std::string, TextureCubeMapSP> allTextures;

private:

	TextureCubeMapManager();
	virtual ~TextureCubeMapManager();

public:

	static TextureCubeMapManager* getInstance();

	static void terminate();

	void addTexture(const std::string& posX, const TextureCubeMapSP& texture);

	TextureCubeMapSP createTexture(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE);

	TextureCubeMapSP createTexture(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE);

};

#endif /* TEXTURECUBEMAPMANAGER_H_ */
