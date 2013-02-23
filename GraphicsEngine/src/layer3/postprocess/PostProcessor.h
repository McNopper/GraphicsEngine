/*
 * PostProcessor.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR_H_
#define POSTPROCESSOR_H_

#include "../../UsedLibs.h"

#include "../../layer0/shader/Program.h"
#include "../../layer0/texture/Texture1D.h"
#include "../../layer2/framebuffer/FrameBuffer.h"

#include "PostProcessorVAO.h"

class PostProcessor
{

protected:

	GLenum target;

	//

	FrameBufferSP frameBuffer;

	FrameBufferSP tempBloomFrameBuffer;
	FrameBufferSP bloomFrameBuffer;

	Texture1DSP blurTexture1D;
	Texture1DSP bloomTexture1D;

	ProgramSP program;

	GLuint vboVertices;
	GLuint vboTexCoords;

	GLuint vboIndices;

	boost::uint32_t numberIndices;

	PostProcessorVAOSP postProcessorVAO;

	//

	bool useBlur;

	bool useBloom;
	float bloomLevel;

	bool useExposure;
	float exposure;

	bool useGamma;
	float gamma;

	PostProcessor(GLenum target);

	virtual void setUniforms() const = 0;

public:

	virtual ~PostProcessor();

	bool use(bool enabled) const;

	void render() const;
	GLuint getVboIndices() const;
	GLuint getVboTexCoords() const;
	GLuint getVboVertices() const;

	bool isUseBlur() const;
	void setUseBlur(bool useBlur);

	bool isUseBloom() const;
	void setUseBloom(bool useBloom);
	float getBloomLevel() const;
	void setBloomLevel(float bloomLevel);

	float getExposure() const;
	void setExposure(float exposure);
	bool isUseExposure() const;
	void setUseExposure(bool useExposure);

	float getGamma() const;
	void setGamma(float gamma);
	bool isUseGamma() const;
	void setUseGamma(bool useGamma);
};

typedef boost::shared_ptr<PostProcessor> PostProcessorSP;

#endif /* POSTPROCESSOR_H_ */
