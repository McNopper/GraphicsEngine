/*
 * PostProcessor2DMultisample.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2DMULTISAMPLE_H_
#define POSTPROCESSOR2DMULTISAMPLE_H_

#include "../../UsedLibs.h"

#include "../../layer0/texture/Texture2D.h"

#include "PostProcessor.h"

class PostProcessor2DMultisample : public PostProcessor
{
private:

	boost::int32_t samples;
	GLenum internalFormat;
	bool fixedsamplelocations;

	Texture2DSP dummy;

protected:

	virtual void setUniforms() const;

public:
	PostProcessor2DMultisample(boost::int32_t samples, GLenum internalFormat, bool fixedsamplelocations, boost::int32_t blurPixel = 2, float blurSigma = 0.5f, boost::int32_t bloomPixel = 16, float bloomSigma = 5.0f);
	virtual ~PostProcessor2DMultisample();
};

typedef boost::shared_ptr<PostProcessor2DMultisample> PostProcessor2DMultisampleSP;

#endif /* POSTPROCESSOR2DMULTISAMPLE_H_ */
