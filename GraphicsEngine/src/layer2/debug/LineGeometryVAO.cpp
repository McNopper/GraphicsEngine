/*
 * LineVAO.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "LineGeometry.h"

#include "LineGeometryVAO.h"

LineGeometryVAO::LineGeometryVAO(const ProgramSP& program, const LineGeometry& lineGeometry) :
		VAO(program)
{
	generateVAO();

	glBindBuffer(GL_ARRAY_BUFFER, lineGeometry.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineGeometry.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

LineGeometryVAO::~LineGeometryVAO()
{
	deleteVAO();
}

