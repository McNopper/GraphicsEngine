/*
 * VAO.h
 *
 *  Created on: 27.04.2011
 *      Author: Norbert Nopper
 */

#ifndef VAO_H_
#define VAO_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "Program.h"

class VAO
{

protected:

	ProgramSP program;

	GLuint vao;

protected:

	void generateVAO();

	void deleteVAO();

public:

	VAO(const ProgramSP& program);
	virtual ~VAO();

	void bind() const;

	void unbind() const;

	const std::string& getProgramType() const;

	const ProgramSP& getProgram() const;

};

typedef boost::shared_ptr<VAO> VAOSP;

#endif /* VAO_H_ */
