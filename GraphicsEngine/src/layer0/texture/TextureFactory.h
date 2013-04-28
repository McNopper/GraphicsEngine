/*
 * TextureFactory.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include "../../UsedLibs.h"

#include "Texture1D.h"
#include "Texture1DArray.h"
#include "Texture2D.h"
#include "Texture2DMultisample.h"
#include "TextureCubeMap.h"

enum FormatDepth {BitsPerPixel8, BitsPerPixel16, BitsPerPixel32};

class TextureFactory
{

private:

	bool autoInternalFloat;
	bool autoInternalInteger;

	enum FormatDepth floatBitsPerPixel;
	enum FormatDepth integerBitsPerPixel;

	GLuint loadImage(const std::string& filename) const;

	GLenum gatherInternalFormat(GLenum format, GLenum type) const;

public:

	TextureFactory();
	virtual ~TextureFactory();

	Texture1DSP createTexture1D(boost::int32_t width, GLenum format, GLenum type, const boost::uint8_t* pixels = nullptr, boost::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	Texture1DSP createTexture1D(GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, const boost::uint8_t* pixels = nullptr, boost::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	//

	Texture1DArraySP createTexture1DArray(boost::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	Texture1DArraySP createTexture1DArray(GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	//

	Texture2DSP createTexture2D(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	Texture2DSP createTexture2D(boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	Texture2DSP createTexture2D(GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	//

	Texture2DMultisampleSP createTexture2DMultisample(boost::int32_t samples, GLint internalFormat, boost::int32_t width, boost::int32_t height, bool fixedsamplelocations) const;

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
	TextureCubeMapSP createTextureCubeMap(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	/**
	 *
	 * Assume, that a DDS cube map is passed.
	 */
	TextureCubeMapSP createTextureCubeMap(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	TextureCubeMapSP createTextureCubeMap(boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	TextureCubeMapSP createTextureCubeMap(GLint internalFormat, boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	bool isAutoInternalFloat() const;
	void setAutoInternalFloat(bool autoInternalFloat);
	bool isAutoInternalInteger() const;
	void setAutoInternalInteger(bool autoInternalInteger);

	enum FormatDepth getFloatBitsPerPixel() const;
	void setFloatBitsPerPixel(enum FormatDepth floatBitsPerPixel);
	enum FormatDepth getIntegerBitsPerPixel() const;
	void setIntegerBitsPerPixel(enum FormatDepth integerBitsPerPixel);
};

#endif /* TEXTUREFACTORY_H_ */
