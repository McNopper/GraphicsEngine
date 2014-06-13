/*
 * PostProcessor2DMultisample.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2DMULTISAMPLE_H_
#define POSTPROCESSOR2DMULTISAMPLE_H_

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2D.h"

#include "PostProcessor.h"

class PostProcessor2DMultisample : public PostProcessor
{
private:

	std::int32_t samples;
	GLenum internalFormat;
	bool fixedsamplelocations;

	Texture2DSP dummy;

protected:

	virtual void setUniforms() const;

public:
	PostProcessor2DMultisample(std::int32_t samples, GLenum internalFormat, bool fixedsamplelocations, std::int32_t blurPixel = 2, float blurSigma = 0.5f, std::int32_t bloomPixel = 16, float bloomSigma = 5.0f, std::int32_t maxRadiusCoC = 16, float cocSigma = 5.0f, float aperture = 10.0f, float focal = 3.0f, float focusedObject = 6.0f);
	virtual ~PostProcessor2DMultisample();
};

typedef std::shared_ptr<PostProcessor2DMultisample> PostProcessor2DMultisampleSP;

#endif /* POSTPROCESSOR2DMULTISAMPLE_H_ */
