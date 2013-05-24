/*
 * PostProcessorVAO.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "PostProcessor.h"

#include "PostProcessorVAO.h"

PostProcessorVAO::PostProcessorVAO(const ProgramSP& program, const PostProcessor& postProcessor) :
		VAO(program)
{
	generateVAO();

	glBindBuffer(GL_ARRAY_BUFFER, postProcessor.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, postProcessor.getVboTexCoords());
	glVertexAttribPointer(program->getAttribLocation(a_texCoord), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, postProcessor.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

PostProcessorVAO::~PostProcessorVAO()
{
	deleteVAO();
}

