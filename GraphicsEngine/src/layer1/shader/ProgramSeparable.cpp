/*
 * ProgramSeparable.cpp
 *
 *  Created on: 27.05.2014
 *      Author: nopper
 */

#include "ProgramSeparable.h"

using namespace std;

ProgramSeparable::ProgramSeparable(const GLUSenum shaderType, const string& filename) :
		shaderType(shaderType), filename(filename)
{
	GLUStextfile source;

	string shaderSource;

	glusLogPrint(GLUS_LOG_INFO, "Loading shader: %s", filename.c_str());

	if(!glusFileLoadText(filename.c_str(), &source))
	{
		return;
	}

	shaderSource = source.text;

	glusFileDestroyText(&source);

	if (!includeShader(shaderSource))
	{
		return;
	}

	const char* finalSource = shaderSource.c_str();

	glusProgramBuildSeparableFromSource(&shaderprogram, shaderType, (const GLUSchar**)&finalSource);
}

ProgramSeparable::~ProgramSeparable()
{
	if (shaderprogram.program)
	{
		glusProgramDestroy(&shaderprogram);
	}
}

bool ProgramSeparable::includeShader(string& shaderSource) const
{
	const string startReplace = "#include<";
	const string endReplace = ">";
	const string functionShader = ".func.";

	string filename;
	string replace;

	size_t startPosition;
	size_t endPosition;

	GLUStextfile source;

	startPosition = shaderSource.find(startReplace);

	while (startPosition != string::npos)
	{
		endPosition = shaderSource.find(endReplace);

		// Check, if include ends (plausible check).

		if (endPosition == string::npos)
		{
			return false;
		}

		filename = shaderSource.substr(startPosition + startReplace.length(), endPosition - (startPosition + startReplace.length()));

		// Only function shader allowed.

		if (filename.find(functionShader) == string::npos)
		{
			return false;
		}

		// Shader not found.

		if(!glusFileLoadText(filename.c_str(), &source))
		{
			return false;
		}

		replace = source.text;

		glusFileDestroyText(&source);

		// Include content from function shader.

		shaderSource.replace(startPosition, endPosition - startPosition + 1, replace);

		// Process all includes.

		startPosition = shaderSource.find(startReplace);
	}

	return true;
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



