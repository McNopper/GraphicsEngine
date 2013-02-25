/*
 * PostProcessor2D.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "../../layer0/algorithm/GaussFilter.h"
#include "../../layer0/renderbuffer/RenderBufferManager.h"
#include "../../layer0/shader/ProgramFactory.h"
#include "../../layer0/shader/Variables.h"
#include "../../layer0/texture/Texture1DManager.h"
#include "../../layer0/texture/Texture2D.h"
#include "../../layer0/texture/Texture2DManager.h"
#include "../../layer0/texture/Texture2DMultisampleManager.h"
#include "../../layer2/framebuffer/FrameBuffer2D.h"
#include "../../layer2/framebuffer/FrameBuffer2DManager.h"


#include "PostProcessor2D.h"

using namespace std;

using namespace boost;

PostProcessor2D::PostProcessor2D(GLenum internalFormat, GLenum format, GLenum type, int32_t blurPixel, float blurSigma, int32_t bloomPixel, float bloomSigma) :
	PostProcessor(GL_TEXTURE_2D), internalFormat(internalFormat), format(format), type(type)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	dummy = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessorDummy", 0, internalFormat, 1, 1, false);

	// Main textures

	Texture2DSP color0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor0" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	Texture2DSP color1Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessor1" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	RenderBufferSP renderBufferDepth = RenderBufferManager::getInstance()->createRenderBuffer("PostProcessor" + uniqueID, GL_DEPTH_COMPONENT, 1, 1);

	FrameBuffer2DSP frameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	frameBuffer2D->setColorAttachment0(color0Texture2D);
	frameBuffer2D->setColorAttachment1(color1Texture2D);
	frameBuffer2D->setDepthAttachment(renderBufferDepth);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessor" + uniqueID, frameBuffer2D, true);

	// Bloom textures ...

	Texture2DSP tempBloomColor0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessorTempBloom" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP tempBloomFrameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	tempBloomFrameBuffer2D->setColorAttachment0(tempBloomColor0Texture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessorTempBloom" + uniqueID, tempBloomFrameBuffer2D, true);

	// ... and final one

	Texture2DSP bloomColor0Texture2D = Texture2DManager::getInstance()->createTexture("PostProcessorBloom" + uniqueID, internalFormat, 1, 1, format, type, false, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	FrameBuffer2DSP bloomFrameBuffer2D = FrameBuffer2DSP(new FrameBuffer2D(1, 1));
	bloomFrameBuffer2D->setColorAttachment0(bloomColor0Texture2D);

	FrameBuffer2DManager::getInstance()->addFrameBuffer("PostProcessorBloom" + uniqueID, bloomFrameBuffer2D, true);

	// Now pass to super class

	frameBuffer = static_cast<FrameBufferSP>(frameBuffer2D);
	tempBloomFrameBuffer = static_cast<FrameBufferSP>(tempBloomFrameBuffer2D);
	bloomFrameBuffer = static_cast<FrameBufferSP>(bloomFrameBuffer2D);

	//

	// Blur textures for bloom and blur pass

	GaussFilter gaussFilterBlur(blurPixel, blurSigma);

	blurTexture1D = Texture1DManager::getInstance()->createTexture("PostProcessorBlur" + uniqueID, GL_R16F, gaussFilterBlur.getValuesSize(), GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBlur.getVoidValues()), gaussFilterBlur.getValuesSize() * 4, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	GaussFilter gaussFilterBloom(bloomPixel, bloomSigma);

	bloomTexture1D = Texture1DManager::getInstance()->createTexture("PostProcessorBloom" + uniqueID, GL_R16F, gaussFilterBloom.getValuesSize(), GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBloom.getVoidValues()), gaussFilterBloom.getValuesSize() * 4, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	//

	screenTexture = u_screenTexture;
	bloomTexture = u_bloomTexture;

	//

	ProgramFactory programFactory;

	program = programFactory.createPostProcess2DProgram();

	GLUSshape rectangularPlane;
	glusCreateRectangularPlanef(&rectangularPlane, 0.5f, 0.5f);

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

	glusDestroyShapef(&rectangularPlane);
}

PostProcessor2D::~PostProcessor2D()
{
}

void PostProcessor2D::setUniforms() const
{
	glUniform1i(program->getUniformLocation(u_numberSamples), 0);
	glUniform1i(program->getUniformLocation(u_useMS), 0);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_screenTextureMS), 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, dummy->getTextureName());
	glUniform1i(program->getUniformLocation(u_bloomTextureMS), 4);

	glActiveTexture(GL_TEXTURE0);
}
