/*
 * ProgramPipeline.h
 *
 *  Created on: 27.05.2014
 *      Author: nopper
 */

#ifndef PROGRAMPIPELINE_H_
#define PROGRAMPIPELINE_H_

#include "../../UsedLibs.h"

#include "ProgramSeparable.h"

class ProgramPipeline
{

protected:

	static ProgramPipeline* lastUsedProgramPipeline;

	GLUSprogrampipeline programpipeline;

	std::string name;

	std::string type;

	ProgramSeparableSP computeProgramSeparable;
	ProgramSeparableSP vertexProgramSeparable;
	ProgramSeparableSP controlProgramSeparable;
	ProgramSeparableSP evaluationProgramSeparable;
	ProgramSeparableSP geometryProgramSeparable;
	ProgramSeparableSP fragmentProgramSeparable;

public:

	static void off();

	ProgramPipeline(const std::string& name, const std::string& type, const ProgramSeparableSP& computeProgramSeparable);
	ProgramPipeline(const std::string& name, const std::string& type, const ProgramSeparableSP& vertexProgramSeparable, const ProgramSeparableSP& fragmentProgramSeparable);
	ProgramPipeline(const std::string& name, const std::string& type, const ProgramSeparableSP& vertexProgramSeparable, ProgramSeparableSP& geometryProgramSeparable, ProgramSeparableSP& fragmentProgramSeparable);
	ProgramPipeline(const std::string& name, const std::string& type, const ProgramSeparableSP& vertexProgramSeparable, const ProgramSeparableSP& controlProgramSeparable, const ProgramSeparableSP& evaluationProgramSeparable, const ProgramSeparableSP& geometryProgramSeparable, const ProgramSeparableSP& fragmentProgramSeparable);
	virtual ~ProgramPipeline();

	void use();

	const std::string& getName() const;

	const std::string& getType() const;

	bool hasComputeProgramSeparable() const;
	const ProgramSeparableSP& getComputeProgramSeparable() const;

	bool hasVertexProgramSeparable() const;
	const ProgramSeparableSP& getVertexProgramSeparable() const;

	bool hasControlProgramSeparable() const;
	const ProgramSeparableSP& getControlProgramSeparable() const;

	bool hasEvaluationProgramSeparable() const;
	const ProgramSeparableSP& getEvaluationProgramSeparable() const;

	bool hasGeometryProgramSeparable() const;
	const ProgramSeparableSP& getGeometryProgramSeparable() const;

	bool hasFragmentProgramSeparable() const;
	const ProgramSeparableSP& getFragmentProgramSeparable() const;

};

typedef std::shared_ptr<ProgramPipeline> ProgramPipelineSP;

#endif /* PROGRAMPIPELINE_H_ */
