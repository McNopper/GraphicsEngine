/*
 * TextureFactory.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTUREFACTORYBASE_H_
#define TEXTUREFACTORYBASE_H_

#include "../../UsedLibs.h"

#include "Texture1D.h"
#include "Texture1DArray.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "Texture2DMultisample.h"
#include "TextureCubeMap.h"
#include "TextureCubeMapArray.h"

enum FormatDepth
{
	BitsPerPixel8, BitsPerPixel16, BitsPerPixel32
};

class TextureFactoryBase
{

protected:

	bool autoInternalFloat;
	bool autoInternalInteger;

	enum FormatDepth floatBitsPerPixel;
	enum FormatDepth integerBitsPerPixel;

	GLenum gatherInternalFormat(GLenum format, GLenum type) const;

	virtual bool saveImage(const std::string& identifier, const PixelData& pixelData) const = 0;

public:

	TextureFactoryBase();
	virtual ~TextureFactoryBase();

	Texture1DSP createTexture1D(const std::string& identifier, std::int32_t width, GLenum format, GLenum type, const std::uint8_t* pixels = nullptr, std::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	Texture1DSP createTexture1D(const std::string& identifier, GLint internalFormat, std::int32_t width, GLenum format, GLenum type, const std::uint8_t* pixels = nullptr, std::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	//

	Texture1DArraySP createTexture1DArray(const std::string& identifier, std::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	Texture1DArraySP createTexture1DArray(const std::string& identifier, GLint internalFormat, std::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	//

	virtual Texture2DSP loadTexture2D(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const = 0;

	Texture2DSP createTexture2D(const std::string& identifier, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	Texture2DSP createTexture2D(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	Texture2DSP createTexture2D(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixels, std::uint32_t sizeOfData, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	//

	Texture2DArraySP createTexture2DArray(const std::string& identifier, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	Texture2DArraySP createTexture2DArray(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;

	//

	Texture2DMultisampleSP createTexture2DMultisample(const std::string& identifier, std::int32_t samples, GLint internalFormat, std::int32_t width, std::int32_t height, bool fixedsamplelocations) const;

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
	virtual TextureCubeMapSP loadTextureCubeMap(const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const = 0;

	/**
	 *
	 * Assume, that a DDS cube map is passed.
	 */
	virtual TextureCubeMapSP loadTextureCubeMap(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const = 0;

	TextureCubeMapSP createTextureCubeMap(const std::string& identifier, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	TextureCubeMapSP createTextureCubeMap(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	virtual TextureCubeMapArraySP loadTextureCubeMapArray(const std::string& identifier, const std::string filename[], std::int32_t sizeOfArray, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const = 0;

	bool isAutoInternalFloat() const;
	void setAutoInternalFloat(bool autoInternalFloat);
	bool isAutoInternalInteger() const;
	void setAutoInternalInteger(bool autoInternalInteger);

	enum FormatDepth getFloatBitsPerPixel() const;
	void setFloatBitsPerPixel(enum FormatDepth floatBitsPerPixel);
	enum FormatDepth getIntegerBitsPerPixel() const;
	void setIntegerBitsPerPixel(enum FormatDepth integerBitsPerPixel);

	//
	// Saving
	//

	bool saveTexture2D(const Texture2DSP texture2D) const;

	bool saveTextureCubeMap(const TextureCubeMapSP textureCubeMap) const;

	bool saveTexture2D(const Texture2DSP texture2D, const std::string& path) const;

	bool saveTextureCubeMap(const TextureCubeMapSP textureCubeMap, const std::string& path) const;

};

#endif /* TEXTUREFACTORYBASE_H_ */
