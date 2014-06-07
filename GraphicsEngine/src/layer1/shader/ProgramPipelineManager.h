/*
 * ProgramPipelineManager.h
 *
 *  Created on: 06.06.2014
 *      Author: nopper
 */

#ifndef PROGRAMPIPELINEMANAGER_H_
#define PROGRAMPIPELINEMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"

#include "ProgramManager.h"
#include "ProgramPipeline.h"

class ProgramPipelineManager : public Singleton<ProgramPipelineManager>
{

	friend class Singleton<ProgramPipelineManager>;

private:

	std::multimap<std::string, ProgramPipelineSP> allProgramPipelines;

private:

	ProgramPipelineManager();
	virtual ~ProgramPipelineManager();

public:

	void addProgramPipeline(const ProgramPipelineSP& programPipeline);

	void removeProgramPipeline(const ProgramPipelineSP& programPipeline);

	ProgramPipelineSP getProgramPipelineBy(const std::string& name, const std::string& type = ProgramManager::DEFAULT_PROGRAM_TYPE) const;

	const std::multimap<std::string, ProgramPipelineSP>& getAllProgramPipelines() const;

};

#endif /* PROGRAMPIPELINEMANAGER_H_ */
