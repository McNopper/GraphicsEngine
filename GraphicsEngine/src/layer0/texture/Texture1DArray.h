/*
 * Texture1DArray.h
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#ifndef TEXTURE1DARRAY_H_
#define TEXTURE1DARRAY_H_

#include "PixelData.h"
#include "TextureStandard.h"

class Texture1DArray : public TextureStandard
{

private:

	std::vector<PixelDataSP> allPixelData;

public:

	Texture1DArray(GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
	virtual ~Texture1DArray();

	virtual bool init();

	virtual void freePixels();

	bool addPixelData(const PixelDataSP& pixelData);

};

typedef boost::shared_ptr<Texture1DArray> Texture1DArraySP;

#endif /* TEXTURE1DARRAY_H_ */
