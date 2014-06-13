/*
 * RenderBufferMultisample.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef RENDERBUFFERMULTISAMPLE_H_
#define RENDERBUFFERMULTISAMPLE_H_

#include "RenderBuffer.h"

class RenderBufferMultisample : public RenderBuffer
{

private:

	std::int32_t samples;

public:
	RenderBufferMultisample(std::int32_t samples, GLenum internalFormat, std::int32_t width, std::int32_t height);
	virtual ~RenderBufferMultisample();

	virtual bool init();

	virtual bool isMultisample() const;

};

typedef std::shared_ptr<RenderBufferMultisample> RenderBufferMultisampleSP;

#endif /* RENDERBUFFERMULTISAMPLE_H_ */
