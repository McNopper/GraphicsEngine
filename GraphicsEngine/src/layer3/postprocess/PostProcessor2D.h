/*
 * PostProcessor.h
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2D_H_
#define POSTPROCESSOR2D_H_

#include "../../UsedLibs.h"

#include "../../layer0/texture/Texture2DMultisample.h"

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

	PostProcessor2D(GLenum internalFormat, GLenum format, GLenum type, boost::int32_t blurPixel = 2, float blurSigma = 0.5f, boost::int32_t bloomPixel = 16, float bloomSigma = 5.0f);
	virtual ~PostProcessor2D();

};

typedef boost::shared_ptr<PostProcessor2D> PostProcessor2DSP;

#endif /* POSTPROCESSOR2D_H_ */
