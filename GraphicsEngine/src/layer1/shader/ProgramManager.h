/*
 * ProgramManager.h
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"

#include "Program.h"

class ProgramManager : public Singleton<ProgramManager>
{

	friend class Singleton<ProgramManager>;

private:

	std::multimap<std::string, ProgramSP> allPrograms;

public:

	static const std::string DEFAULT_PROGRAM_TYPE;
	static const std::string RENDER_TO_CUBEMAP_PROGRAM_TYPE;
	static const std::string RENDER_TO_SHADOWMAP_PROGRAM_TYPE;

private:

	ProgramManager();
	virtual ~ProgramManager();

public:

	void addProgram(const ProgramSP& program);

	void removeProgram(const ProgramSP& program);

	ProgramSP getComputeProgramBy(const std::string& computeFilename, const std::string& type = DEFAULT_PROGRAM_TYPE) const;

	ProgramSP getVertexFragmentProgramBy(const std::string& vertexFilename, const std::string& fragmentFilename, const std::string& type = DEFAULT_PROGRAM_TYPE) const;

	ProgramSP getVertexGeometryFragmentProgramBy(const std::string& vertexFilename, const std::string& geometryFilename, const std::string& fragmentFilename, const std::string& type = DEFAULT_PROGRAM_TYPE) const;

	ProgramSP getVertexControlEvaluateGeometryFragmentProgramBy(const std::string& vertexFilename, const std::string& controlFilename, const std::string& evaluationFilename, const std::string& geometryFilename, const std::string& fragmentFilename, const std::string& type = DEFAULT_PROGRAM_TYPE) const;

	const std::multimap<std::string, ProgramSP>& getAllPrograms() const;

};

#endif /* PROGRAMMANAGER_H_ */
