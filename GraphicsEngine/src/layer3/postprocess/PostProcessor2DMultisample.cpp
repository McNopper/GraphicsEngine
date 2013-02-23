/*
 * PostProcessor2DMultisample.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "../../layer0/algorithm/GaussFilter.h"
#include "../../layer0/renderbuffer/RenderBufferMultisampleManager.h"
#include "../../layer0/shader/ProgramFactory.h"
#include "../../layer0/shader/Variables.h"
#include "../../layer0/texture/Texture1DManager.h"
#include "../../layer0/texture/Texture2DMultisample.h"
#include "../../layer0/texture/Texture2DMultisampleManager.h"
#include "../../layer2/framebuffer/FrameBuffer2DMultisample.h"
#include "../../layer2/framebuffer/FrameBuffer2DMultisampleManager.h"

#include "PostProcessor2DMultisample.h"

using namespace std;

using namespace boost;

PostProcessor2DMultisample::PostProcessor2DMultisample(int32_t samples, GLenum internalFormat, bool fixedsamplelocations, int32_t blurPixel, float blurSigma, int32_t bloomPixel, float bloomSigma) :
	PostProcessor(GL_TEXTURE_2D_MULTISAMPLE), samples(samples), internalFormat(internalFormat), fixedsamplelocations(fixedsamplelocations)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	// Main textures

	Texture2DMultisampleSP color0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor0Multisample" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);
	Texture2DMultisampleSP color1Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessor1Multisample" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	RenderBufferMultisampleSP renderBufferMultisampleDepth = RenderBufferMultisampleManager::getInstance()->createRenderBuffer("PostProcessorMultisample" + uniqueID, samples, GL_DEPTH_COMPONENT, 1, 1);

	FrameBuffer2DMultisampleSP frameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	frameBuffer2DMultisample->setColorAttachment0(color0Texture2DMultisample);
	frameBuffer2DMultisample->setColorAttachment1(color1Texture2DMultisample);
	frameBuffer2DMultisample->setDepthAttachment(renderBufferMultisampleDepth);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessorMultisample" + uniqueID, frameBuffer2DMultisample, true);

	// Bloom textures ...

	Texture2DMultisampleSP tempBloomColor0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessorTempBloomMultisample" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP tempBloomFrameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	tempBloomFrameBuffer2DMultisample->setColorAttachment0(tempBloomColor0Texture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessorTempBloomMultisample" + uniqueID, tempBloomFrameBuffer2DMultisample, true);

	// ... and final one

	Texture2DMultisampleSP bloomColor0Texture2DMultisample = Texture2DMultisampleManager::getInstance()->createTexture("PostProcessorBloomMultisample" + uniqueID, samples, internalFormat, 1, 1, fixedsamplelocations);

	FrameBuffer2DMultisampleSP bloomFrameBuffer2DMultisample = FrameBuffer2DMultisampleSP(new FrameBuffer2DMultisample(1, 1));
	bloomFrameBuffer2DMultisample->setColorAttachment0(bloomColor0Texture2DMultisample);

	FrameBuffer2DMultisampleManager::getInstance()->addFrameBuffer("PostProcessorBloomMultisample" + uniqueID, bloomFrameBuffer2DMultisample, true);

	// Now pass to super class

	frameBuffer = static_cast<FrameBufferSP>(frameBuffer2DMultisample);
	tempBloomFrameBuffer = static_cast<FrameBufferSP>(tempBloomFrameBuffer2DMultisample);
	bloomFrameBuffer = static_cast<FrameBufferSP>(bloomFrameBuffer2DMultisample);

	//

	// Blur textures for bloom and blur pass

	GaussFilter gaussFilterBlur(blurPixel, blurSigma);

	blurTexture1D = Texture1DManager::getInstance()->createTexture("PostProcessorBlurMultisample" + uniqueID, GL_R16F, gaussFilterBlur.getValuesSize(), GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBlur.getVoidValues()), gaussFilterBlur.getValuesSize() * 4, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	GaussFilter gaussFilterBloom(bloomPixel, bloomSigma);

	bloomTexture1D = Texture1DManager::getInstance()->createTexture("PostProcessorBloomMultisample" + uniqueID, GL_R16F, gaussFilterBloom.getValuesSize(), GL_RED, GL_FLOAT, static_cast<const uint8_t*>(gaussFilterBloom.getVoidValues()), gaussFilterBloom.getValuesSize() * 4, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	//

	ProgramFactory programFactory;

	program = programFactory.createPostProcess2DMultisampleProgram();

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

PostProcessor2DMultisample::~PostProcessor2DMultisample()
{
}

void PostProcessor2DMultisample::setUniforms() const
{
	glUniform1i(program->getUniformLocation(u_numberSamples), samples);
}
