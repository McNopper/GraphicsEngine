/*
 * SkyVAO.cpp
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "Sky.h"

#include "SkyVAO.h"

SkyVAO::SkyVAO(const ProgramSP& program, const Sky& sky) : VAO(program)
{
	generateVAO();

	glBindBuffer(GL_ARRAY_BUFFER, sky.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sky.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

SkyVAO::~SkyVAO()
{
	deleteVAO();
}

