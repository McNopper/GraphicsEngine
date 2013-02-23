/*
 * PostProcessor2D.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "../../layer0/shader/Variables.h"
#include "../../layer1/camera/Camera.h"
#include "../../layer1/camera/CameraManager.h"
#include "../../layer1/camera/ViewportManager.h"

#include "PostProcessor.h"

using namespace std;

using namespace boost;

PostProcessor::PostProcessor(GLenum target) :
		target(target), frameBuffer(), tempBloomFrameBuffer(), bloomFrameBuffer(), blurTexture1D(), bloomTexture1D(), program(), vboVertices(0), vboTexCoords(0), vboIndices(0), numberIndices(0), useBlur(false), useBloom(false), bloomLevel(1.0f), useExposure(false), exposure(1.0f), useGamma(false), gamma(2.2f)
{
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
	if (!frameBuffer.get() || !tempBloomFrameBuffer.get() || !bloomFrameBuffer.get() || !blurTexture1D.get() || !bloomTexture1D.get() )
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

	// Create bloom textures
	if (useBloom)
	{
		use(false);

		// Only the bright texture is needed
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(target, frameBuffer->getColor1Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(u_screenTexture), 0);

		// Not used. Just take the color texture as a dummy value
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(target, frameBuffer->getColor0Texture()->getTextureName());
		glUniform1i(program->getUniformLocation(u_bloomTexture), 1);

		// Blur using the bloom texture
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_1D, bloomTexture1D->getTextureName());
		glUniform1i(program->getUniformLocation(u_blurTexture), 2);

		glActiveTexture(GL_TEXTURE0);

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
		tempBloomFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		tempBloomFrameBuffer->use(false);

		// ... and final pass

		glBindTexture(target, tempBloomFrameBuffer->getColor0Texture()->getTextureName());

		glUniform1i(program->getUniformLocation(u_blurHorizontal), 0);
		glUniform1i(program->getUniformLocation(u_blurVertical), 1);
		bloomFrameBuffer->use(true);

		glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

		bloomFrameBuffer->use(false);

		//

		postProcessorVAO->unbind();

		glBindTexture(target, 0);
	}

	//

	use(false);

	// Color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(target, frameBuffer->getColor0Texture()->getTextureName());
	glUniform1i(program->getUniformLocation(u_screenTexture), 0);

	// Bloom
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(target, bloomFrameBuffer->getColor0Texture()->getTextureName());
	glUniform1i(program->getUniformLocation(u_bloomTexture), 1);

	// Blur
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, blurTexture1D->getTextureName());
	glUniform1i(program->getUniformLocation(u_blurTexture), 2);

	glActiveTexture(GL_TEXTURE0);

	glUniform1i(program->getUniformLocation(u_useBlur), useBlur);
	glUniform1i(program->getUniformLocation(u_blurHorizontal), 1);
	glUniform1i(program->getUniformLocation(u_blurVertical), 1);

	glUniform1i(program->getUniformLocation(u_useBloom), useBloom);
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
