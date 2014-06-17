/*
 * TextureFactory_DevIL.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTUREFACTORY_DEVIL_H_
#define TEXTUREFACTORY_DEVIL_H_

#include <IL/il.h>
#include <IL/ilu.h>

#include "TextureFactoryBase.h"

class TextureFactory : public TextureFactoryBase
{

protected:

	ILuint loadImage(const std::string& filename, std::string& identifier) const;

	virtual bool saveImage(const std::string& identifier, const PixelData& pixelData) const;

public:

	TextureFactory();
	virtual ~TextureFactory();

	virtual Texture2DSP loadTexture2D(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	/**
	 * If you have DirectX images, convert the following way before usage:
	 *
	 * pos_x - Flip and mirror image
	 * neg_x - Flip and mirror image
	 * pos_y - Keep
	 * neg_y - Keep
	 * pos_z - Flip and mirror image. Set as neg_z
	 * neg_z - Flip and mirror image. Set as pos_z
	 */
	virtual TextureCubeMapSP loadTextureCubeMap(const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	/**
	 *
	 * Assume, that a DDS cube map is passed.
	 */
	virtual TextureCubeMapSP loadTextureCubeMap(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	virtual TextureCubeMapArraySP loadTextureCubeMapArray(const std::string& identifier, const std::string filename[], std::int32_t sizeOfArray, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

};

#endif /* TEXTUREFACTORY_DEVIL_H_ */
