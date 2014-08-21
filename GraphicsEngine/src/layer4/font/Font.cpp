/*
 * Font.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer1/shader/ProgramFactory.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer1/texture/Texture2DManager.h"
#include "../../layer3/camera/CameraManager.h"
#include "../../layer3/camera/ViewportManager.h"

#include "Font.h"

using namespace std;

Font::Font(const string& filename, float width, float height, int32_t columns, int32_t rows, float cellWidth, float cellHeight, float fontWidth, float fontHeight) :
		width(width), height(height), columns(columns), rows(rows), cellWidth(cellWidth), cellHeight(cellHeight), fontWidth(fontWidth), fontHeight(fontHeight)
{
	cellWidthNormalized = cellWidth / width;
	cellHeightNormalized = cellHeight / height;

	fontTextureName = Texture2DManager::getInstance()->createTexture(filename, false, GL_LINEAR, GL_LINEAR)->getTextureName();

	camera = CameraManager::getInstance()->getDefaultOrthographicCamera();

	ProgramFactory programFactory;
	program = programFactory.createFontProgram();

	GLUSshape rectangularPlane;
	glusShapeCreateRectangularPlanef(&rectangularPlane, cellWidth / 2.0f, cellHeight / 2.0f);

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

	fontVAO = FontVAOSP(new FontVAO(program, *this));

	glusShapeDestroyf(&rectangularPlane);
}

Font::~Font()
{
	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboTexCoords);

	glDeleteBuffers(1, &vboIndices);

	fontVAO.reset();

	program.reset();

	camera.reset();
}

GLuint Font::getVboVertices() const
{
    return vboVertices;
}

GLuint Font::getVboTexCoords() const
{
    return vboTexCoords;
}

GLuint Font::getVboIndices() const
{
    return vboIndices;
}

void Font::internalPrint(float x, float y, const Color& color, const char* output) const
{
	program->use();

	glUniformMatrix4fv(program->getUniformLocation(u_projectionMatrix), 1, GL_FALSE, camera->getProjectionMatrix().getM());
	glUniformMatrix4fv(program->getUniformLocation(u_viewMatrix), 1, GL_FALSE, camera->getViewMatrix().getM());

	glUniform1f(program->getUniformLocation(u_fontWidth), cellWidthNormalized);
	glUniform1f(program->getUniformLocation(u_fontHeight), cellHeightNormalized);

	glUniform4fv(program->getUniformLocation(u_fontColor), 1, color.getRGBA());

	glBindTexture(GL_TEXTURE_2D, fontTextureName);
	glUniform1i(program->getUniformLocation(u_fontTexture), 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	ViewportSP currentViewport = ViewportManager::getInstance()->getDefaultViewport();

	Matrix4x4 modelMatrix;
	Matrix4x4 toScreenMatrix;
	toScreenMatrix.translate(-static_cast<float>(currentViewport->getWidth()) / 2.0f + cellWidth / 2.0f, static_cast<float>(currentViewport->getHeight()) / 2.0f - cellHeight / 2.0f, 0.0f);

	fontVAO->bind();

	char c;
	float currentColumnNormalized;
	float currentRowNormalized;
	float currentX = x;
	float currentY = y;
	int32_t stringLength = strlen(output);
	for (int32_t i = 0; i < stringLength; i++)
	{
		c = output[i];

		if (c != '\n')
		{
			currentColumnNormalized = static_cast<float>(c % columns) * cellWidth / width;
			currentRowNormalized = 1.0f - static_cast<float>(c / rows) * cellHeight / height - cellHeightNormalized;

			glUniform1f(program->getUniformLocation(u_fontLeft), currentColumnNormalized);
			glUniform1f(program->getUniformLocation(u_fontTop), currentRowNormalized);

			modelMatrix.identity();
			modelMatrix.translate(currentX, -currentY, 0.0f);
			modelMatrix.multiply(toScreenMatrix);

			glUniformMatrix4fv(program->getUniformLocation(u_modelMatrix), 1, GL_FALSE, modelMatrix.getM());

			glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

			currentX += fontWidth;
		}
		else
		{
			currentX = x;
			currentY += fontHeight;
		}
	}

	fontVAO->unbind();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::print(float x, float y, const Color& color, const char* output, ...) const
{
	const uint32_t MAXCHARS = 2047;
	char buffer[MAXCHARS + 1];
	buffer[MAXCHARS] = '\0';

	va_list argList;
	va_start(argList, output);

	vsnprintf(buffer, MAXCHARS, output, argList);

	va_end(argList);

	internalPrint(x, y, color, buffer);
}

void Font::print(float x, float y, const Color& color, const string& output) const
{
	internalPrint(x, y, color, output.c_str());
}
