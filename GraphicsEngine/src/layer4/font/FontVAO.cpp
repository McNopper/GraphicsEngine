/*
 * FontVAO.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "Font.h"

#include "FontVAO.h"

FontVAO::FontVAO(const ProgramSP& program, const Font& font) :
		VAO(program)
{
	generateVAO();

	glBindBuffer(GL_ARRAY_BUFFER, font.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, font.getVboTexCoords());
	glVertexAttribPointer(program->getAttribLocation(a_texCoord), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, font.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

FontVAO::~FontVAO()
{
	deleteVAO();
}

