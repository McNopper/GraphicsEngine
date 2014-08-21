/*
 * PostProcessor2D.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "../../layer0/filter/GaussFilter.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer1/texture/Texture1DArrayManager.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/camera/CameraManager.h"
#include "../../layer3/camera/ViewportManager.h"

#include "PostProcessor.h"

using namespace std;

PostProcessor::PostProcessor(GLenum target, int32_t blurPixel, float blurSigma, int32_t bloomPixel, float bloomSigma, int32_t maxRadiusCoC, float cocSigma, float aperture, float focal, float focusedObject) :
		target(target), outputFramebuffer(0), frameBuffer(), tempFrameBuffer(), depthOfFieldFrameBuffer(), bloomFrameBuffer(), blurTexture1DArray(), bloomTexture1DArray(), program(), vboVertices(0), vboTexCoords(0), vboIndices(0), numberIndices(0), useDoF(false), aperture(aperture), focal(focal), focusedObject(focusedObject), useBlur(false), useBloom(false), bloomLevel(1.0f), useExposure(false), exposure(1.0f), useGamma(false), gamma(2.2f)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	// Blur textures for bloom, blur and depth of field pass

	GaussFilter gaussFilterBlur(blurPixel, blurSigma);
	PixelDataSP pixelDataBlur = PixelDataSP(new PixelData(gaussFilterBlur.getValuesSize(), 1, GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBlur.getVoidValues()), gaussFilterBlur.getValuesSize() * 4));

	blurTexture1DArray = Texture1DArrayManager::getInstance()->createTexture("PostProcessorBlur" + uniqueID, GL_R16F, gaussFilterBlur.getValuesSize(), GL_RED, GL_FLOAT, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	blurTexture1DArray->addPixelData(pixelDataBlur);
	blurTexture1DArray->init();

	GaussFilter gaussFilterBloom(bloomPixel, bloomSigma);
	PixelDataSP pixelDataBloom = PixelDataSP(new PixelData(gaussFilterBloom.getValuesSize(), 1, GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBloom.getVoidValues()), gaussFilterBloom.getValuesSize() * 4));

	bloomTexture1DArray = Texture1DArrayManager::getInstance()->createTexture("PostProcessorBloom" + uniqueID, GL_R16F, gaussFilterBloom.getValuesSize(), GL_RED, GL_FLOAT, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	bloomTexture1DArray->addPixelData(pixelDataBloom);
	bloomTexture1DArray->init();

	GaussFilter gaussFilterCoC(maxRadiusCoC, cocSigma);
	depthOfFieldTexture1DArray = Texture1DArrayManager::getInstance()->createTexture("PostProcessorDepthOfField" + uniqueID, GL_R16F, gaussFilterCoC.getValuesSize(), GL_RED, GL_FLOAT, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	for (int32_t i = maxRadiusCoC; i > 0; i--)
	{
		GaussFilter gaussFilterCoC(i, cocSigma);
		PixelDataSP pixelDataCoC = PixelDataSP(new PixelData(gaussFilterCoC.getValuesSize(), 1, GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterCoC.getVoidValues()), gaussFilterCoC.getValuesSize() * 4));

		depthOfFieldTexture1DArray->addPixelData(pixelDataCoC);
	}
	depthOfFieldTexture1DArray->init();
}

PostProcessor::~PostProcessor()
{
	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboTexCoords);

	glDeleteBuffers(1, &vboIndices);

	postProcessorVAO.reset();

	program.reset();
}

bool PostProcessor::use(bool enabled) const
{
	if (frameBuffer.get())
	{
		frameBuffer->use(enabled);

		if (!enabled)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer);
		}

		return true;
	}

	return false;
}

GLuint PostProcessor::getVboIndices() const
{
	return vboIndices;
}

GLuint PostProcessor::getVboTexCoords() const
{
	return vboTexCoords;
}

GLuint PostProcessor::getVboVertices() const
{
	return vboVertices;
}

void PostProcessor::render() const
{
	if (!frameBuffer.get() || !tempFrameBuffer.get() || !bloomFrameBuffer.get() || !depthOfFieldFrameBuffer.get() || !blurTexture1DArray.get() || !bloomTexture1DArray.get() || !depthOfFieldTexture1DArray.get() )
	{
		return;
	}

	CameraSP currentCamera = CameraManager::getInstance()->getDefaultOrthographicCamera();

	Matrix4x4 modelMatrix;
	modelMatrix.scale(static_cast<GLfloat>(frameBuffer->getWidth()), static_cast<GLfloat>(frameBuffer->getHeight()), 1.0f);

	program->use();

	setUniforms();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glUniformMatrix4fv(program->getUniformLocation(u_projectionMatrix), 1, GL_FALSE, currentCamera->getProjectionMatrix().getM());
	glUniformMatrix4fv(program->getUniformLocation(u_viewMatrix), 1, GL_FALSE, currentCamera->getViewMatrix().getM());
	glUniformMatrix4fv(program->getUniformLocation(u_modelMatrix), 1, GL_FALSE, modelMatrix.getM());

	//

	const CameraSP& defaultCamera = CameraManager::getInstance()->getDefaultPerspectiveCamera();

	Point4 focalPoint = defaultCamera->getEye() + (defaultCamera->getDirection() * focal);
	Point4 focusedObjectPoint = defaultCamera->getEye() + (defaultCamera->getDirection() * focusedObject);

	Point4 biasedFocalPoint = defaultCamera->getBiasedProjectionMatrix() * defaultCamera->getViewMatrix() * focalPoint;
	Point4 biasedFocusedObjectPoint = defaultCamera->getBiasedProjectionMatrix() * defaultCamera->getViewMatrix() * focusedObjectPoint;

	glUniform1f(program->getUniformLocation(u_aperture), aperture);
	glUniform1f(program->getUniformLocation(u_focal), glusMathClampf(biasedFocalPoint.getZ(), 0.0f, 1.0f));
	glUniform1f(program->getUniformLocation(u_focusedObject), glusMathClampf(biasedFocusedObjectPoint.getZ(), 0.0f, 1.0f));

	//

	// Depth texture
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(target, frameBuffer->getDepthTexture()->getTextureName());
	glUniform1i(program->getUniformLocation(depthTexture), 3);

	glActiveTexture(GL_TEXTURE0);

	// Create bloom textures
	if (useBloom)
	{
		use(false);

		// Only the bright texture is needed
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(target, frameBuffer->getColor1Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(screenTexture), 0);

		// Not used. Just take the color texture as a dummy value
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(target, frameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(bloomTexture), 1);

		// Blur using the bloom texture
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_1D_ARRAY, bloomTexture1DArray->getTextureName());
		glUniform1i(program->getUniformLocation(u_blurTexture), 2);

		glActiveTexture(GL_TEXTURE0);

		glUniform1i(program->getUniformLocation(u_useDoF), false);

		glUniform1i(program->getUniformLocation(u_useBlur), true);

		glUniform1i(program->getUniformLocation(u_useBloom), false);
		glUniform1f(program->getUniformLocation(u_bloomLevel), bloomLevel);

		glUniform1i(program->getUniformLocation(u_useExposure), false);
		glUniform1f(program->getUniformLocation(u_exposure), exposure);

		glUniform1i(program->getUniformLocation(u_useGamma), false);
		glUniform1f(program->getUniformLocation(u_gamma), gamma);

		postProcessorVAO->bind();

		// First pass ...

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 1);
		glUniform1i(program->getUniformLocation(u_blurVertical), 0);
		tempFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		tempFrameBuffer->use(false);

		// ... and final pass

		glBindTexture(target, tempFrameBuffer->getColor0Texture()->getTextureName());

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 0);
		glUniform1i(program->getUniformLocation(u_blurVertical), 1);

		bloomFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		bloomFrameBuffer->use(false);

		//

		postProcessorVAO->unbind();

		glBindTexture(target, 0);
	}

	FrameBufferSP usedFrameBuffer = frameBuffer;

	// Bloom the framebuffer
	if (useBloom)
	{
		use(false);

		// Original frame buffer
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(target, frameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(screenTexture), 0);

		// Bloom
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(target, bloomFrameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(bloomTexture), 1);

		// Dummy
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_1D_ARRAY, bloomTexture1DArray->getTextureName());
		glUniform1i(program->getUniformLocation(u_blurTexture), 2);

		glActiveTexture(GL_TEXTURE0);

		glUniform1i(program->getUniformLocation(u_useDoF), false);

		glUniform1i(program->getUniformLocation(u_useBlur), false);

		glUniform1i(program->getUniformLocation(u_useBloom), true);
		glUniform1f(program->getUniformLocation(u_bloomLevel), bloomLevel);

		glUniform1i(program->getUniformLocation(u_useExposure), false);
		glUniform1f(program->getUniformLocation(u_exposure), exposure);

		glUniform1i(program->getUniformLocation(u_useGamma), false);
		glUniform1f(program->getUniformLocation(u_gamma), gamma);

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 0);
		glUniform1i(program->getUniformLocation(u_blurVertical), 0);

		postProcessorVAO->bind();

		// One pass

		tempFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		tempFrameBuffer->use(false);

		//

		postProcessorVAO->unbind();

		glBindTexture(target, 0);

		usedFrameBuffer = tempFrameBuffer;
	}

	// Depth of field
	if (useDoF)
	{
		use(false);

		// Only the color texture is needed
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(target, usedFrameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(screenTexture), 0);

		// Not used. Just take the color texture as a dummy value
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(target, frameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(bloomTexture), 1);

		// Blur using the DOF texture
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_1D_ARRAY, depthOfFieldTexture1DArray->getTextureName());
		glUniform1i(program->getUniformLocation(u_blurTexture), 2);

		glActiveTexture(GL_TEXTURE0);

		glUniform1i(program->getUniformLocation(u_useDoF), true);

		glUniform1i(program->getUniformLocation(u_useBlur), false);

		glUniform1i(program->getUniformLocation(u_useBloom), false);
		glUniform1f(program->getUniformLocation(u_bloomLevel), bloomLevel);

		glUniform1i(program->getUniformLocation(u_useExposure), false);
		glUniform1f(program->getUniformLocation(u_exposure), exposure);

		glUniform1i(program->getUniformLocation(u_useGamma), false);
		glUniform1f(program->getUniformLocation(u_gamma), gamma);

		postProcessorVAO->bind();

		// First pass ...

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 1);
		glUniform1i(program->getUniformLocation(u_blurVertical), 0);
		tempFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		tempFrameBuffer->use(false);

		// ... and final pass

		glBindTexture(target, tempFrameBuffer->getColor0Texture()->getTextureName());

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 0);
		glUniform1i(program->getUniformLocation(u_blurVertical), 1);
		depthOfFieldFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		depthOfFieldFrameBuffer->use(false);

		//

		postProcessorVAO->unbind();

		glBindTexture(target, 0);

		usedFrameBuffer = depthOfFieldFrameBuffer;
	}

	//

	use(false);

	// Color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(target, usedFrameBuffer->getColor0Texture()->getTextureName());
	glUniform1i(program->getUniformLocation(screenTexture), 0);

	// Not used.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(target, bloomFrameBuffer->getColor0Texture()->getTextureName());
	glUniform1i(program->getUniformLocation(bloomTexture), 1);

	// Blur
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D_ARRAY, blurTexture1DArray->getTextureName());
	glUniform1i(program->getUniformLocation(u_blurTexture), 2);

	glActiveTexture(GL_TEXTURE0);

	glUniform1i(program->getUniformLocation(u_useDoF), false);

	glUniform1i(program->getUniformLocation(u_useBlur), useBlur);
	glUniform1i(program->getUniformLocation(u_blurHorizontal), 1);
	glUniform1i(program->getUniformLocation(u_blurVertical), 1);

	glUniform1i(program->getUniformLocation(u_useBloom), false);
	glUniform1f(program->getUniformLocation(u_bloomLevel), bloomLevel);

	glUniform1i(program->getUniformLocation(u_useExposure), useExposure);
	glUniform1f(program->getUniformLocation(u_exposure), exposure);

	glUniform1i(program->getUniformLocation(u_useGamma), useGamma);
	glUniform1f(program->getUniformLocation(u_gamma), gamma);

	postProcessorVAO->bind();

	glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

	postProcessorVAO->unbind();

	//

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glBindTexture(target, 0);
}

GLuint PostProcessor::getOutputFBO() const
{
	return outputFramebuffer;
}

void PostProcessor::setOutputFBO(GLuint outputFramebuffer)
{
	this->outputFramebuffer = outputFramebuffer;
}

GLuint PostProcessor::getFBO() const
{
	if (frameBuffer.get())
	{
		return frameBuffer->getFBO();
	}

	return 0;
}

bool PostProcessor::isUseDoF() const
{
	return useDoF;
}

void PostProcessor::setUseDoF(bool useDoF)
{
	this->useDoF = useDoF;
}

float PostProcessor::getAperture() const
{
	return aperture;
}

void PostProcessor::setAperture(float aperture)
{
	this->aperture = aperture;
}

float PostProcessor::getFocal() const
{
	return focal;
}

void PostProcessor::setFocal(float focal)
{
	this->focal = focal;
}

float PostProcessor::getFocusedObject() const
{
	return focusedObject;
}

void PostProcessor::setFocusedObject(float focusedObject)
{
	this->focusedObject = focusedObject;
}

bool PostProcessor::isUseBlur() const
{
	return useBlur;
}

void PostProcessor::setUseBlur(bool useBlur)
{
	this->useBlur = useBlur;
}

bool PostProcessor::isUseBloom() const
{
	return useBloom;
}

void PostProcessor::setUseBloom(bool useBloom)
{
	this->useBloom = useBloom;
}

float PostProcessor::getBloomLevel() const
{
	return bloomLevel;
}

void PostProcessor::setBloomLevel(float bloomLevel)
{
	this->bloomLevel = bloomLevel;
}

float PostProcessor::getExposure() const
{
	return exposure;
}

void PostProcessor::setExposure(float exposure)
{
	if (exposure < 0.0f)
	{
		return;
	}

	this->exposure = exposure;
}

bool PostProcessor::isUseExposure() const
{
	return useExposure;
}

void PostProcessor::setUseExposure(bool useExposure)
{
	this->useExposure = useExposure;
}

float PostProcessor::getGamma() const
{
	return gamma;
}

void PostProcessor::setGamma(float gamma)
{
	if (gamma <= 0.0f)
	{
		return;
	}

	this->gamma = gamma;
}

bool PostProcessor::isUseGamma() const
{
	return useGamma;
}

void PostProcessor::setUseGamma(bool useGamma)
{
	this->useGamma = useGamma;
}
