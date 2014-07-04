/*
 * GlTfSampler.cpp
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#include "GlTfSampler.h"

GlTfSampler::GlTfSampler(GLenum magFilter, GLenum minFilter, GLenum wrapS, GLenum wrapT) :
	magFilter(magFilter), minFilter(minFilter), wrapS(wrapS), wrapT(wrapT)
{
}

GlTfSampler::~GlTfSampler()
{
}

GLenum GlTfSampler::getMagFilter() const
{
	return magFilter;
}

GLenum GlTfSampler::getMinFilter() const
{
	return minFilter;
}

GLenum GlTfSampler::getWrapS() const
{
	return wrapS;
}

GLenum GlTfSampler::getWrapT() const
{
	return wrapT;
}
