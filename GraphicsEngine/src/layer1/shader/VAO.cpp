/*
 * VAO.cpp
 *
 *  Created on: 27.04.2011
 *      Author: Norbert Nopper
 */

#include "GL/glus.h"

#include "VAO.h"

using namespace std;

VAO::VAO(const ProgramSP& program) :
	program(program), vao(0)
{
}

VAO::~VAO()
{
}

void VAO::generateVAO()
{
	glGenVertexArrays(1, &vao);
	bind();
}

void VAO::deleteVAO()
{
	unbind();
	glDeleteVertexArrays(1, &vao);
}

void VAO::bind() const
{
	glBindVertexArray(vao);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

const string& VAO::getProgramType() const
{
	return program->getType();
}

const ProgramSP& VAO::getProgram() const
{
	return program;
}
