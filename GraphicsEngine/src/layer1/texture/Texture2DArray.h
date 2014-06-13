/*
 * Texture2DArray.h
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#ifndef TEXTURE2DARRAY_H_
#define TEXTURE2DARRAY_H_

#include "PixelData.h"
#include "TextureStandard.h"

class Texture2DArray : public TextureStandard
{

private:

	std::vector<PixelDataSP> allPixelData;

public:

	Texture2DArray(const std::string& identifier, GLint internalFormat, std::int32_t width, std::int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~Texture2DArray();

	virtual bool init();

	virtual void freePixels();

	bool addPixelData(const PixelDataSP& pixelData);

};

typedef std::shared_ptr<Texture2DArray> Texture2DArraySP;

#endif /* TEXTURE2DARRAY_H_ */
