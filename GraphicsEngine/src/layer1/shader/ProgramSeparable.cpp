/*
 * ProgramSeparable.cpp
 *
 *  Created on: 27.05.2014
 *      Author: nopper
 */

#include "ProgramSeparable.h"

using namespace std;

using namespace boost;

ProgramSeparable::ProgramSeparable(const GLUSenum shaderType, const string& filename) :
		shaderType(shaderType), filename(filename)
{
	GLUStextfile source;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s", filename.c_str());

	glusLoadTextFile(filename.c_str(), &source);

	glusBuildShaderProgramFromSource(&shaderprogram, shaderType, (const GLUSchar**) &source.text);

	glusDestroyTextFile(&source);
}

ProgramSeparable::~ProgramSeparable()
{
	if (shaderprogram.program)
	{
		glusDestroyProgram(&shaderprogram);
	}
}

int32_t ProgramSeparable::getUniformLocation(const string& name)
{
	auto found = allUniforms.find(name);

	if (found != allUniforms.end())
	{
		return found->second;
	}
	int32_t uniformLocation = glGetUniformLocation(shaderprogram.program, name.c_str());
	allUniforms[name] = uniformLocation;

	return uniformLocation;
}

int32_t ProgramSeparable::getAttribLocation(const string& name)
{
	auto found = allAtribbs.find(name);

	if (found != allAtribbs.end())
	{
		return found->second;
	}
	int32_t attribLocation = glGetAttribLocation(shaderprogram.program, name.c_str());
	allAtribbs[name] = attribLocation;

	return attribLocation;
}

const GLUSuint ProgramSeparable::getProgram() const
{
	return shaderprogram.program;
}

const GLUSenum ProgramSeparable::getShaderType() const
{
	return shaderType;
}

const string& ProgramSeparable::getFilename() const
{
	return filename;
}



