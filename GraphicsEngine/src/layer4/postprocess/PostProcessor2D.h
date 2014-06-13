/*
 * PostProcessor.h
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2D_H_
#define POSTPROCESSOR2D_H_

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2DMultisample.h"

#include "PostProcessor.h"

class PostProcessor2D : public PostProcessor
{

private:

	GLenum internalFormat;
	GLenum format;
	GLenum type;

	Texture2DMultisampleSP dummy;

protected:

	virtual void setUniforms() const;

public:

	PostProcessor2D(GLenum internalFormat, GLenum format, GLenum type, std::int32_t blurPixel = 2, float blurSigma = 0.5f, std::int32_t bloomPixel = 16, float bloomSigma = 5.0f, std::int32_t maxRadiusCoC = 16, float cocSigma = 5.0f, float aperture = 10.0f, float focal = 3.0f, float focusedObject = 6.0f);
	virtual ~PostProcessor2D();

};

typedef std::shared_ptr<PostProcessor2D> PostProcessor2DSP;

#endif /* POSTPROCESSOR2D_H_ */
