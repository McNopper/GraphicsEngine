/*
 * TextureCubeMapArrayManager.h
 *
 *  Created on: 14.06.2014
 *      Author: nopper
 */

#ifndef TEXTURECUBEMAPARRAYMANAGER_H_
#define TEXTURECUBEMAPARRAYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "TextureCubeMapArray.h"

class TextureCubeMapArrayManager : public Singleton<TextureCubeMapArrayManager>
{

	friend class Singleton<TextureCubeMapArrayManager>;

private:

	KeyValueMap<std::string, TextureCubeMapArraySP> allTextures;

private:

	TextureCubeMapArrayManager();
	virtual ~TextureCubeMapArrayManager();

public:

	void addTexture(const std::string& identifier, const TextureCubeMapArraySP& texture);

	TextureCubeMapArraySP createTexture(const std::string& identifier, const std::string filename[], std::int32_t sizeOfArray, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);

};

#endif /* TEXTURECUBEMAPARRAYMANAGER_H_ */
