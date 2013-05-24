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

	boost::int32_t samples;

public:
	RenderBufferMultisample(boost::int32_t samples, GLenum internalFormat, boost::int32_t width, boost::int32_t height);
	virtual ~RenderBufferMultisample();

	virtual bool init();

	virtual bool isMultisample() const;

};

typedef boost::shared_ptr<RenderBufferMultisample> RenderBufferMultisampleSP;

#endif /* RENDERBUFFERMULTISAMPLE_H_ */
