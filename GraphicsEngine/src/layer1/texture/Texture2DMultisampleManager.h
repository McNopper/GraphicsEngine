/*
 * Texture2DMultisampleManager.h
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#ifndef TEXTURE2DMULTISAMPLEMANAGER_H_
#define TEXTURE2DMULTISAMPLEMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Texture2DMultisample.h"

class Texture2DMultisampleManager : public Singleton<Texture2DMultisampleManager>
{

	friend class Singleton<Texture2DMultisampleManager>;

private:

	KeyValueMap<std::string, Texture2DMultisampleSP> allTextures;

private:

	Texture2DMultisampleManager();
	virtual ~Texture2DMultisampleManager();

public:

	void addTexture(const std::string& key, const Texture2DMultisampleSP& texture);

	Texture2DMultisampleSP createTexture(const std::string& key, std::int32_t samples, GLint internalFormat, std::int32_t width, std::int32_t height, bool fixedsamplelocations = false);

};

#endif /* TEXTURE2DMULTISAMPLEMANAGER_H_ */
