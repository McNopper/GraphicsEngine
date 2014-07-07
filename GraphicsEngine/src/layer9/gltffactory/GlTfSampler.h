/*
 * GlTfSampler.h
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#ifndef GLTFSAMPLER_H_
#define GLTFSAMPLER_H_

#include "../../UsedLibs.h"

class GlTfSampler
{

private:

	GLenum magFilter;
	GLenum minFilter;
	GLenum wrapS;
	GLenum wrapT;

public:

	GlTfSampler(GLenum magFilter, GLenum minFilter, GLenum wrapS, GLenum wrapT);
	virtual ~GlTfSampler();

	GLenum getMagFilter() const;
	GLenum getMinFilter() const;
	GLenum getWrapS() const;
	GLenum getWrapT() const;

};

typedef std::shared_ptr<GlTfSampler> GlTfSamplerSP;

#endif /* GLTFSAMPLER_H_ */
