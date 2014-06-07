/*
 * ProgramPipelineManager.cpp
 *
 *  Created on: 06.06.2014
 *      Author: nopper
 */

#include "ProgramPipelineManager.h"

using namespace std;

ProgramPipelineManager::ProgramPipelineManager() :
		Singleton<ProgramPipelineManager>(), allProgramPipelines()
{
}

ProgramPipelineManager::~ProgramPipelineManager()
{
}

void ProgramPipelineManager::addProgramPipeline(const ProgramPipelineSP& programPipeline)
{
	allProgramPipelines.insert(pair<string, ProgramPipelineSP>(programPipeline->getType(), programPipeline));
}

void ProgramPipelineManager::removeProgramPipeline(const ProgramPipelineSP& programPipeline)
{
	auto walker = allProgramPipelines.find(programPipeline->getType());

	while (walker != allProgramPipelines.end())
	{
		if (walker->second == programPipeline)
		{
			allProgramPipelines.erase(walker);

			return;
		}

		walker++;
	}
}

ProgramPipelineSP ProgramPipelineManager::getProgramPipelineBy(const string& name, const string& type) const
{
	auto walker = allProgramPipelines.begin();

	ProgramPipelineSP currentProgramPipeline;
	while (walker != allProgramPipelines.end())
	{
		currentProgramPipeline = walker->second;

		if (currentProgramPipeline->getName().compare(name) == 0 && currentProgramPipeline->getType().compare(type) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	return ProgramPipelineSP();
}

const multimap<string, ProgramPipelineSP>& ProgramPipelineManager::getAllProgramPipelines() const
{
	return allProgramPipelines;
}

