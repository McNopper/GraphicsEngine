/*
 * Ground.cpp
 *
 *  Created on: 16.05.2013
 *      Author: nopper
 */

#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/ProgramFactory.h"

#include "Ground.h"

using namespace std;

Ground::Ground(const BoundingSphere& boundingSphere, const GridPlaneShape& gridPlaneShape) :
		boundingSphere(boundingSphere), numberVertices(gridPlaneShape.getShape().numberVertices), numberIndices(gridPlaneShape.getShape().numberIndices), allVAOs()
{
	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*)gridPlaneShape.getShape().vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*)gridPlaneShape.getShape().normals, GL_STATIC_DRAW);

	glGenBuffers(1, &vboBitangents);
	glBindBuffer(GL_ARRAY_BUFFER, vboBitangents);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*)gridPlaneShape.getShape().bitangents, GL_STATIC_DRAW);

	glGenBuffers(1, &vboTangents);
	glBindBuffer(GL_ARRAY_BUFFER, vboTangents);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*)gridPlaneShape.getShape().tangents, GL_STATIC_DRAW);

	glGenBuffers(1, &vboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 2 * sizeof(GLfloat), (GLfloat*)gridPlaneShape.getShape().texCoords, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndices * sizeof(GLuint), (GLuint*)gridPlaneShape.getShape().indices, GL_STATIC_DRAW);

	//

	ProgramFactory programFactory;

	ProgramSP shaderprogram = programFactory.createGroundProgram();

	GroundVAOSP vao = GroundVAOSP(new GroundVAO(shaderprogram, *this));
	addVAO(vao);

	shaderprogram = programFactory.createGroundRenderToCubeMapProgram();

	vao = GroundVAOSP(new GroundVAO(shaderprogram, *this));
	addVAO(vao);

	shaderprogram = programFactory.createGroundRenderToShadowMapProgram();

	vao = GroundVAOSP(new GroundVAO(shaderprogram, *this));
	addVAO(vao);
}

Ground::~Ground()
{
	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboNormals);
	glDeleteBuffers(1, &vboBitangents);
	glDeleteBuffers(1, &vboTangents);
	glDeleteBuffers(1, &vboTexCoords);

	glDeleteBuffers(1, &vboIndices);

	//

	auto walker = allVAOs.begin();
	while (walker != allVAOs.end())
	{
		walker->second.reset();

		walker++;
	}
	allVAOs.clear();
}

void Ground::addVAO(const GroundVAOSP& vao)
{
	allVAOs[vao->getProgramType()] = vao;
}

const BoundingSphere& Ground::getBoundingSphere() const
{
	return boundingSphere;
}

uint32_t Ground::getNumberVertices() const
{
	return numberVertices;
}

GLuint Ground::getVboVertices() const
{
	return vboVertices;
}

GLuint Ground::getVboNormals() const
{
	return vboNormals;
}

GLuint Ground::getVboBitangents() const
{
	return vboBitangents;
}

GLuint Ground::getVboTangents() const
{
	return vboTangents;
}

GLuint Ground::getVboTexCoords() const
{
	return vboTexCoords;
}

uint32_t Ground::getNumberIndices() const
{
	return numberIndices;
}

GLuint Ground::getVboIndices() const
{
	return vboIndices;
}

bool Ground::containsVAOByProgramType(const string& type) const
{
	return allVAOs.find(type) != allVAOs.end();
}

const GroundVAOSP& Ground::getVAOByProgramType(const string& type) const
{
	return allVAOs.at(type);
}
