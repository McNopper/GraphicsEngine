/*
 * Program.cpp
 *
 *  Created on: 26.04.2011
 *      Author: Norbert Nopper
 */

#include "Program.h"

using namespace std;

Program *Program::lastUsedProgram = 0;

void Program::off()
{
	glUseProgram(0);

	lastUsedProgram = 0;
}

Program::Program(const string& type, const string& computeFilename) :
	type(type), computeFilename(computeFilename), vertexFilename(""), controlFilename(""), evaluationFilename(""), geometryFilename(""), fragmentFilename(), allUniforms(), allAtribbs()
{
	GLUStextfile computeSource;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s", computeFilename.c_str());

	glusFileLoadText(computeFilename.c_str(), &computeSource);

	glusProgramBuildComputeFromSource(&shaderprogram, (const GLUSchar**) &computeSource.text);

	glusFileDestroyText(&computeSource);
}

Program::Program(const string& type, const string& vertexFilename, const string& fragmentFilename) :
	type(type), computeFilename(""), vertexFilename(vertexFilename), controlFilename(""), evaluationFilename(""), geometryFilename(""), fragmentFilename(fragmentFilename), allUniforms(), allAtribbs()
{
	GLUStextfile vertexSource;
	GLUStextfile fragmentSource;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s %s", vertexFilename.c_str(), fragmentFilename.c_str());

	glusFileLoadText(vertexFilename.c_str(), &vertexSource);
	glusFileLoadText(fragmentFilename.c_str(), &fragmentSource);

	glusProgramBuildFromSource(&shaderprogram, (const GLUSchar**) &vertexSource.text, 0, 0, 0, (const GLUSchar**) &fragmentSource.text);

	glusFileDestroyText(&vertexSource);
	glusFileDestroyText(&fragmentSource);
}

Program::Program(const string& type, const string& vertexFilename, const string& geometryFilename, const string& fragmentFilename) :
	type(type), computeFilename(""), vertexFilename(vertexFilename), controlFilename(""), evaluationFilename(""), geometryFilename(geometryFilename), fragmentFilename(fragmentFilename), allUniforms(), allAtribbs()
{
	GLUStextfile vertexSource;
	GLUStextfile geometrySource;
	GLUStextfile fragmentSource;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s %s %s", vertexFilename.c_str(), geometryFilename.c_str(), fragmentFilename.c_str());

	glusFileLoadText(vertexFilename.c_str(), &vertexSource);
	glusFileLoadText(geometryFilename.c_str(), &geometrySource);
	glusFileLoadText(fragmentFilename.c_str(), &fragmentSource);

	glusProgramBuildFromSource(&shaderprogram, (const GLUSchar**) &vertexSource.text, 0, 0, (const GLUSchar**) &geometrySource.text, (const GLUSchar**) &fragmentSource.text);

	glusFileDestroyText(&vertexSource);
	glusFileDestroyText(&geometrySource);
	glusFileDestroyText(&fragmentSource);
}

Program::Program(const string& type, const string& vertexFilename, const string& controlFilename, const string& evaluationFilename, const string& geometryFilename, const string& fragmentFilename) :
	type(type), computeFilename(""), vertexFilename(vertexFilename), controlFilename(controlFilename), evaluationFilename(evaluationFilename), geometryFilename(geometryFilename), fragmentFilename(fragmentFilename), allUniforms(), allAtribbs()
{
	GLUStextfile vertexSource;
	GLUStextfile controlSource;
	GLUStextfile evaluationSource;
	GLUStextfile geometrySource;
	GLUStextfile fragmentSource;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s %s %s %s %s", vertexFilename.c_str(), controlFilename.c_str(), evaluationFilename.c_str(), geometryFilename.c_str(), fragmentFilename.c_str());

	glusFileLoadText(vertexFilename.c_str(), &vertexSource);
	glusFileLoadText(controlFilename.c_str(), &controlSource);
	glusFileLoadText(evaluationFilename.c_str(), &evaluationSource);
	glusFileLoadText(geometryFilename.c_str(), &geometrySource);
	glusFileLoadText(fragmentFilename.c_str(), &fragmentSource);

	glusProgramBuildFromSource(&shaderprogram, (const GLUSchar**) &vertexSource.text, (const GLUSchar**) &controlSource.text, (const GLUSchar**) &evaluationSource.text, (const GLUSchar**) &geometrySource.text, (const GLUSchar**) &fragmentSource.text);

	glusFileDestroyText(&vertexSource);
	glusFileDestroyText(&controlSource);
	glusFileDestroyText(&evaluationSource);
	glusFileDestroyText(&geometrySource);
	glusFileDestroyText(&fragmentSource);
}

Program::~Program()
{
	if (shaderprogram.program)
	{
		if (lastUsedProgram == this)
		{
			off();
		}

		glusProgramDestroy(&shaderprogram);
	}

	allUniforms.clear();
	allAtribbs.clear();
}

bool Program::operator ==(const Program& other) const
{
	return this->vertexFilename.compare(other.vertexFilename) == 0 && this->fragmentFilename.compare(other.fragmentFilename) == 0;
}

void Program::use()
{
	if (lastUsedProgram != this)
	{
		glUseProgram(shaderprogram.program);

		lastUsedProgram = this;
	}
}

int32_t Program::getUniformLocation(const string& name)
{
	map<string, int32_t>::iterator found = allUniforms.find(name);

	if (found != allUniforms.end())
	{
		return found->second;
	}
	int32_t uniformLocation = glGetUniformLocation(shaderprogram.program, name.c_str());
	allUniforms[name] = uniformLocation;

	return uniformLocation;
}

int32_t Program::getAttribLocation(const string& name)
{
	map<string, int32_t>::iterator found = allAtribbs.find(name);

	if (found != allAtribbs.end())
	{
		return found->second;
	}
	int32_t attribLocation = glGetAttribLocation(shaderprogram.program, name.c_str());
	allAtribbs[name] = attribLocation;

	return attribLocation;
}

const string& Program::getType() const
{
	return type;
}

const string& Program::getComputeFilename() const
{
	return computeFilename;
}

const string& Program::getVertexFilename() const
{
	return vertexFilename;
}

const string& Program::getControlFilename() const {
	return controlFilename;
}

const string& Program::getEvaluationFilename() const {
	return evaluationFilename;
}

const string& Program::getGeometryFilename() const {
	return geometryFilename;
}

const string& Program::getFragmentFilename() const
{
	return fragmentFilename;
}
