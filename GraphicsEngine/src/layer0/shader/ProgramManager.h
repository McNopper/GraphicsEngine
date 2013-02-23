/*
 * ProgramManager.h
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include "../../UsedLibs.h"

#include "Program.h"

class ProgramManager
{
private:

	static ProgramManager* instance;

	std::multimap<std::string, ProgramSP> allPrograms;

public:

	static const std::string DEFAULT_PROGRAM_TYPE;

private:

	ProgramManager();
	virtual ~ProgramManager();

public:

	static ProgramManager* getInstance();

	static void terminate();

	void addProgram(const ProgramSP& program);

	void removeProgram(const ProgramSP& program);

	ProgramSP getProgramBy(const std::string& computeFilename) const;

	ProgramSP getProgramBy(const std::string& vertexFilename, const std::string& fragmentFilename) const;

	ProgramSP getProgramBy(const std::string& vertexFilename, const std::string& geometryFilename, const std::string& fragmentFilename) const;

	ProgramSP getProgramBy(const std::string& vertexFilename, const std::string& controlFilename, const std::string& evaluationFilename, const std::string& geometryFilename, const std::string& fragmentFilename) const;

	const std::multimap<std::string, ProgramSP>& getAllPrograms() const;

};

#endif /* PROGRAMMANAGER_H_ */
