/*
 * Sky.cpp
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#include "../../layer1/shader/ProgramFactory.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer1/texture/TextureCubeMapManager.h"

#include "Sky.h"

using namespace std;

Sky::Sky(const Shape& shape, float radiusX, float radiusY, float radiusZ, const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ) : vboVertices(0), vboIndices(0), writeBrightColor(false), brightColorLimit(1.0f)
{
	ProgramFactory programFactory;
	program = programFactory.createSkyProgram();

	numberIndices = shape.getShape().numberIndices;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER,
			shape.getShape().numberVertices * 4 * sizeof(GLfloat),
			(GLfloat*) shape.getShape().vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			shape.getShape().numberIndices * sizeof(GLuint),
			(GLuint*) shape.getShape().indices, GL_STATIC_DRAW);

	skyVAO = SkyVAOSP(new SkyVAO(program, *this));

	//

	scaleMatrix.scale(radiusX, radiusY, radiusZ);

	//

	skyTexture = TextureCubeMapManager::getInstance()->createTexture(identifier, posX, negX, posY, negY, posZ, negZ);
}

Sky::Sky(const Shape& shape, float radiusX, float radiusY, float radiusZ, const string& filename) : vboVertices(0), vboIndices(0), writeBrightColor(false), brightColorLimit(1.0f)
{
	ProgramFactory programFactory;
	program = programFactory.createSkyProgram();

	numberIndices = shape.getShape().numberIndices;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER,
			shape.getShape().numberVertices * 4 * sizeof(GLfloat),
			(GLfloat*) shape.getShape().vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			shape.getShape().numberIndices * sizeof(GLuint),
			(GLuint*) shape.getShape().indices, GL_STATIC_DRAW);

	skyVAO = SkyVAOSP(new SkyVAO(program, *this));

	//

	scaleMatrix.scale(radiusX, radiusY, radiusZ);

	//

	skyTexture = TextureCubeMapManager::getInstance()->createTexture(filename);
}

Sky::~Sky()
{
	skyTexture.reset();

	//

	glDeleteBuffers(1, &vboVertices);

	glDeleteBuffers(1, &vboIndices);

	skyVAO.reset();

	program.reset();
}

GLuint Sky::getVboVertices() const
{
	return vboVertices;
}

GLuint Sky::getVboIndices() const
{
	return vboIndices;
}

void Sky::render(const Point4& center) const
{
	Matrix4x4 translationMatrix;
	translationMatrix.translate(center.getX(), center.getY(), center.getZ());

    glFrontFace(GL_CW);

    if (skyTexture.get())
    {
    	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture->getTextureName());
    }
    else
    {
    	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

	program->use();

	glUniformMatrix4fv(program->getUniformLocation(u_modelMatrix), 1, GL_FALSE, (translationMatrix * scaleMatrix).getM());

    glUniform1i(program->getUniformLocation(u_cubemap), 0);

	// Write bright color
	glUniform1i(program->getUniformLocation(u_writeBrightColor), writeBrightColor);
	glUniform1f(program->getUniformLocation(u_brightColorLimit), brightColorLimit);

	skyVAO->bind();

	glDrawElements(GL_TRIANGLES, numberIndices, GL_UNSIGNED_INT, 0);

	skyVAO->unbind();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glFrontFace(GL_CCW);
}

GLuint Sky::getSkyTextureName() const
{
	if (skyTexture.get())
	{
		return skyTexture->getTextureName();
	}

	return 0;
}

bool Sky::isWriteBrightColor() const
{
	return writeBrightColor;
}

float Sky::getBrightColorLimit() const
{
	return brightColorLimit;
}

void Sky::setWriteBrightColor(bool writeBrightColor)
{
	this->writeBrightColor = writeBrightColor;
}

void Sky::setBrightColorLimit(float brightColorLimit)
{
	this->brightColorLimit = brightColorLimit;
}


