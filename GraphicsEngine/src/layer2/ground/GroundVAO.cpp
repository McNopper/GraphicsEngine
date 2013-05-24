/*
 * GroundVAO.cpp
 *
 *  Created on: 17.05.2013
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "Ground.h"

#include "GroundVAO.h"

GroundVAO::GroundVAO(const ProgramSP& program, const Ground& ground) :
		VAO(program)
{
	generateVAO();

	update(ground);
}

GroundVAO::~GroundVAO()
{
	deleteVAO();
}


void GroundVAO::update(const Ground& ground) const
{
	glBindBuffer(GL_ARRAY_BUFFER, ground.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, ground.getVboNormals());
	glVertexAttribPointer(program->getAttribLocation(a_normal), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_normal));

	glBindBuffer(GL_ARRAY_BUFFER, ground.getVboBitangents());
	glVertexAttribPointer(program->getAttribLocation(a_bitangent), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_bitangent));

	glBindBuffer(GL_ARRAY_BUFFER, ground.getVboTangents());
	glVertexAttribPointer(program->getAttribLocation(a_tangent), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_tangent));

	glBindBuffer(GL_ARRAY_BUFFER, ground.getVboTexCoords());
	glVertexAttribPointer(program->getAttribLocation(a_texCoord), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ground.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

