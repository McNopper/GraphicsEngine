/*
 * ProgramSeparable.h
 *
 *  Created on: 27.05.2014
 *      Author: nopper
 */

#ifndef PROGRAMSEPARABLE_H_
#define PROGRAMSEPARABLE_H_

#include "../../UsedLibs.h"

class ProgramSeparable
{

protected:

	GLUSshaderprogram shaderprogram;

	GLUSenum shaderType;

	std::string filename;

	std::map<std::string, boost::int32_t> allUniforms;
	std::map<std::string, boost::int32_t> allAtribbs;

	bool includeShader(std::string& shaderSource) const;

public:

	ProgramSeparable(const GLUSenum shaderType, const std::string& filename);
	virtual ~ProgramSeparable();

	boost::int32_t getUniformLocation(const std::string& name);
	boost::int32_t getAttribLocation(const std::string& name);

	const GLUSuint getProgram() const;

	const GLUSenum getShaderType() const;

	const std::string& getFilename() const;

};

typedef boost::shared_ptr<ProgramSeparable> ProgramSeparableSP;

#endif /* PROGRAMSEPARABLE_H_ */
