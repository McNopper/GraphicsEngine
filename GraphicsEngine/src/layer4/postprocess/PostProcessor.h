/*
 * PostProcessor.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR_H_
#define POSTPROCESSOR_H_

#include "../../UsedLibs.h"

#include "../../layer1/shader/Program.h"
#include "../../layer1/texture/Texture1DArray.h"
#include "../../layer2/framebuffer/FrameBuffer.h"

#include "PostProcessorVAO.h"

class PostProcessor
{

protected:

	GLenum target;

	//

	GLuint  outputFramebuffer;

	//

	FrameBufferSP frameBuffer;
	FrameBufferSP tempFrameBuffer;

	FrameBufferSP depthOfFieldFrameBuffer;

	FrameBufferSP bloomFrameBuffer;

	Texture1DArraySP blurTexture1DArray;
	Texture1DArraySP bloomTexture1DArray;
	Texture1DArraySP depthOfFieldTexture1DArray;

	ProgramSP program;

	GLuint vboVertices;
	GLuint vboTexCoords;

	GLuint vboIndices;

	std::uint32_t numberIndices;

	PostProcessorVAOSP postProcessorVAO;

	//

	bool useDoF;
	float aperture;
	float focal;
	float focusedObject;

	bool useBlur;

	bool useBloom;
	float bloomLevel;

	bool useExposure;
	float exposure;

	bool useGamma;
	float gamma;

	std::string screenTexture;
	std::string depthTexture;
	std::string bloomTexture;

	PostProcessor(GLenum target, std::int32_t blurPixel = 2, float blurSigma = 0.5f, std::int32_t bloomPixel = 16, float bloomSigma = 5.0f, std::int32_t maxRadiusCoC = 16, float cocSigma = 5.0f, float aperture = 10.0f, float focal = 3.0f, float focusedObject = 6.0f);

	virtual void setUniforms() const = 0;

public:

	virtual ~PostProcessor();

	bool use(bool enabled) const;

	void render() const;
	GLuint getVboIndices() const;
	GLuint getVboTexCoords() const;
	GLuint getVboVertices() const;

	GLuint getOutputFBO() const;
	void setOutputFBO(GLuint outputFramebuffer);

	GLuint getFBO() const;

	bool isUseDoF() const;
	void setUseDoF(bool useDoF);
	float getAperture() const;
	void setAperture(float aperture);
	float getFocal() const;
	void setFocal(float focal);
	float getFocusedObject() const;
	void setFocusedObject(float focusedObject);
	
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

typedef std::shared_ptr<PostProcessor> PostProcessorSP;

#endif /* POSTPROCESSOR_H_ */
