/*
 * PostProcessor2D.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "../../layer1/renderbuffer/RenderBufferManager.h"
#include "../../layer1/shader/ProgramFactory.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer1/texture/Texture2D.h"
#include "../../layer1/texture/Texture2DManager.h"
#include "../../layer1/texture/Texture2DMultisampleManager.h"
#include "../../layer2/framebuffer/FrameBuffer2D.h"
#include "../../layer2/framebuffer/FrameBuffer2DManager.h"


#include "PostProcessor2D.h"

using namespace std;

PostProcessor2D::PostProcessor2D(GLenum internalFormat, GLenum format, GLenum type, int32_t blurPixel, float blurSigma, int32_t bloomPixel, float bloomSigma, int32_t maxRadiusCoC, float cocSigma, float aperture, float focal, float focusedObject) :
	PostProcessor(GL_TEXTURE_2D, blurPixel, blurSigma, bloomPixel, bloomSigma, maxRadiusCoC, cocSigma, aperture, focal, focusedObject), internalFormat(internalFormat), format(format), type(type)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	dummy = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor2DDummy", 0, internalFormat, 1, 1, false);

	// Main textures

	Texture2DSP color0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2D0" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	Texture2DSP color1Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2D1" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	Texture2DSP depthTexture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2DDepth" + uniqueID, GL_DEPTH_COMPONENT, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP frameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	frameBuffer2D->setColorAttachment0(color0Texture2D);
	frameBuffer2D->setColorAttachment1(color1Texture2D);
	frameBuffer2D->setDepthAttachment(depthTexture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessor2D" + uniqueID, frameBuffer2D, true);

	// Temporary

	Texture2DSP tempColor0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2DTemp" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP tempFrameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	tempFrameBuffer2D->setColorAttachment0(tempColor0Texture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessor2DTemp" + uniqueID, tempFrameBuffer2D, true);

	// Depth of Field textures ...

	Texture2DSP depthOfFieldColor0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2DDepthOfField" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP depthOfFieldFrameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	depthOfFieldFrameBuffer2D->setColorAttachment0(depthOfFieldColor0Texture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessor2DDepthOfField" + uniqueID, depthOfFieldFrameBuffer2D, true);

	// Bloom textures ...

	Texture2DSP bloomColor0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor2DBloom" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP bloomFrameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	bloomFrameBuffer2D->setColorAttachment0(bloomColor0Texture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessor2DBloom" + uniqueID, bloomFrameBuffer2D, true);

	// Now pass to super class

	frameBuffer = static_cast<FrameBufferSP>(frameBuffer2D);
	tempFrameBuffer = static_cast<FrameBufferSP>(tempFrameBuffer2D);
	depthOfFieldFrameBuffer = static_cast<FrameBufferSP>(depthOfFieldFrameBuffer2D);
	bloomFrameBuffer = static_cast<FrameBufferSP>(bloomFrameBuffer2D);

	//

	screenTexture = u_screenTexture;
	depthTexture = u_depthTexture;
	bloomTexture = u_bloomTexture;

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

PostProcessor2D::~PostProcessor2D()
{
}

void PostProcessor2D::setUniforms() const
{
	glUniform1i(program->getUniformLocation(u_numberSamples), 0);
	glUniform1i(program->getUniformLocation(u_useMS), 0);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_screenTextureMS), 4);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_bloomTextureMS), 5);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_depthTextureMS), 6);

	glActiveTexture(GL_TEXTURE0);
}
