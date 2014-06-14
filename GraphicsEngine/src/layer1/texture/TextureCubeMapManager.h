/*
 * TextureCubeMapManager.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTURECUBEMAPMANAGER_H_
#define TEXTURECUBEMAPMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "TextureCubeMap.h"

class TextureCubeMapManager : public Singleton<TextureCubeMapManager>
{

	friend class Singleton<TextureCubeMapManager>;

private:

	KeyValueMap<std::string, TextureCubeMapSP> allTextures;

private:

	TextureCubeMapManager();
	virtual ~TextureCubeMapManager();

public:

	void addTexture(const std::string& identifier, const TextureCubeMapSP& texture);

	TextureCubeMapSP createTexture(const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);

	TextureCubeMapSP createTexture(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);

};

#endif /* TEXTURECUBEMAPMANAGER_H_ */
