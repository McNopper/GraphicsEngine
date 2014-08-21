/*
 * PostProcessor2DMultisample.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "../../layer0/filter/GaussFilter.h"
#include "../../layer1/renderbuffer/RenderBufferMultisampleManager.h"
#include "../../layer1/shader/ProgramFactory.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer1/texture/Texture2DManager.h"
#include "../../layer1/texture/Texture2DMultisample.h"
#include "../../layer1/texture/Texture2DMultisampleManager.h"
#include "../../layer2/framebuffer/FrameBuffer2DMultisample.h"
#include "../../layer2/framebuffer/FrameBuffer2DMultisampleManager.h"

#include "PostProcessor2DMultisample.h"

using namespace std;

PostProcessor2DMultisample::PostProcessor2DMultisample(int32_t samples, GLenum internalFormat, bool fixedsamplelocations, int32_t blurPixel, float blurSigma, int32_t bloomPixel, float bloomSigma, int32_t maxRadiusCoC, float cocSigma, float aperture, float focal, float focusedObject) :
	PostProcessor(GL_TEXTURE_2D_MULTISAMPLE, blurPixel, blurSigma, bloomPixel, bloomSigma, maxRadiusCoC, cocSigma, aperture, focal, focusedObject), samples(samples), internalFormat(internalFormat), fixedsamplelocations(fixedsamplelocations)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	dummy = Texture2DManager::getInstance()->createTexture("PostProcessor2DMultisampleDummy", GL_RGB, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	// Main textures

	Texture2DMultisampleSP color0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisample0" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);
	Texture2DMultisampleSP color1Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisample1" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	Texture2DMultisampleSP depthTexture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisampleDepth" + uniqueID, samples, GL_DEPTH_COMPONENT, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP frameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	frameBuffer2DMultisample->setColorAttachment0(color0Texture2DMultisample);
	frameBuffer2DMultisample->setColorAttachment1(color1Texture2DMultisample);
	frameBuffer2DMultisample->setDepthAttachment(depthTexture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessor2DMultisample" + uniqueID, frameBuffer2DMultisample, true);

	// Temporary

	Texture2DMultisampleSP tempColor0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisampleTemp" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP tempFrameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	tempFrameBuffer2DMultisample->setColorAttachment0(tempColor0Texture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessor2DMultisampleTemp" + uniqueID, tempFrameBuffer2DMultisample, true);

	// Depth of Field textures ...

	Texture2DMultisampleSP depthOfFieldColor0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisampleDepthOfField" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP depthOfFieldFrameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	depthOfFieldFrameBuffer2DMultisample->setColorAttachment0(depthOfFieldColor0Texture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessor2DMultisampleDepthOfField" + uniqueID, depthOfFieldFrameBuffer2DMultisample, true);

	// Bloom textures ...

	Texture2DMultisampleSP bloomColor0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DMultisampleBloom" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP bloomFrameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	bloomFrameBuffer2DMultisample->setColorAttachment0(bloomColor0Texture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessor2DMultisampleBloom" + uniqueID, bloomFrameBuffer2DMultisample, true);

	// Now pass to super class

	frameBuffer = static_cast<FrameBufferSP>(frameBuffer2DMultisample);
	tempFrameBuffer = static_cast<FrameBufferSP>(tempFrameBuffer2DMultisample);
	depthOfFieldFrameBuffer = static_cast<FrameBufferSP>(depthOfFieldFrameBuffer2DMultisample);
	bloomFrameBuffer = static_cast<FrameBufferSP>(bloomFrameBuffer2DMultisample);

	//

	screenTexture = u_screenTextureMS;
	depthTexture = u_depthTextureMS;
	bloomTexture = u_bloomTextureMS;

	//

	ProgramFactory programFactory;

	program = programFactory.createPostProcess2DProgram();

	GLUSshape rectangularPlane;
	glusShapeCreateRectangularPlanef(&rectangularPlane, 0.5f, 0.5f);

	numberIndices = rectangularPlane.numberIndices;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, rectangularPlane.numberVertices * 4 * sizeof(GLfloat), (GLfloat*) rectangularPlane.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, rectangularPlane.numberVertices * 2 * sizeof(GLfloat), (GLfloat*) rectangularPlane.texCoords, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rectangularPlane.numberIndices * sizeof(GLuint), (GLuint*) rectangularPlane.indices, GL_STATIC_DRAW);

	postProcessorVAO = PostProcessorVAOSP(new PostProcessorVAO(program, *this));

	glusShapeDestroyf(&rectangularPlane);
}

PostProcessor2DMultisample::~PostProcessor2DMultisample()
{
}

void PostProcessor2DMultisample::setUniforms() const
{
	glUniform1i(program->getUniformLocation(u_numberSamples), samples);
	glUniform1i(program->getUniformLocation(u_useMS), 1);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_screenTexture), 4);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_bloomTexture), 5);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_depthTexture), 6);

	glActiveTexture(GL_TEXTURE0);
}
