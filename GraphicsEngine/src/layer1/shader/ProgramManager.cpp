/*
 * ProgramManager.cpp
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#include "Variables.h"

#include "ProgramManager.h"

using namespace std;

const string ProgramManager::DEFAULT_PROGRAM_TYPE = "default";
const string ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE = "renderToCubeMap";
const string ProgramManager::RENDER_TO_SHADOWMAP_PROGRAM_TYPE = "renderToShadowMap";

ProgramManager::ProgramManager() :
		Singleton<ProgramManager>(), allPrograms()
{
}

ProgramManager::~ProgramManager()
{
	multimap<string, ProgramSP>::iterator walker = allPrograms.begin();
	while (walker != allPrograms.end())
	{
		walker->second.reset();
		walker++;
	}
	allPrograms.clear();
}

void ProgramManager::addProgram(const ProgramSP& program)
{
	allPrograms.insert(pair<string, ProgramSP>(program->getType(), program));
}

void ProgramManager::removeProgram(const ProgramSP& program)
{
	multimap<string, ProgramSP>::iterator walker = allPrograms.find(program->getType());

	while (walker != allPrograms.end())
	{
		if (walker->second == program)
		{
			allPrograms.erase(walker);

			return;
		}

		walker++;
	}
}

ProgramSP ProgramManager::getComputeProgramBy(const string& computeFilename, const string& type) const
{
	multimap<string, ProgramSP>::const_iterator walker = allPrograms.begin();

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;

		if (currentProgram->getComputeFilename().compare(computeFilename) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	currentProgram = ProgramSP(new Program(type, computeFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getVertexFragmentProgramBy(const string& vertexFilename, const string& fragmentFilename, const string& type) const
{
	multimap<string, ProgramSP>::const_iterator walker = allPrograms.begin();

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;

		if (currentProgram->getVertexFilename().compare(vertexFilename) == 0 && currentProgram->getFragmentFilename().compare(fragmentFilename) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	currentProgram = ProgramSP(new Program(type, vertexFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getVertexGeometryFragmentProgramBy(const string& vertexFilename, const string& geometryFilename, const string& fragmentFilename, const string& type) const
{
	multimap<string, ProgramSP>::const_iterator walker = allPrograms.begin();

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;

		if (currentProgram->getVertexFilename().compare(vertexFilename) == 0 && currentProgram->getGeometryFilename().compare(geometryFilename) == 0 && currentProgram->getFragmentFilename().compare(fragmentFilename) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	currentProgram = ProgramSP(new Program(type, vertexFilename, geometryFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getVertexControlEvaluateGeometryFragmentProgramBy(const std::string& vertexFilename, const std::string& controlFilename, const std::string& evaluationFilename, const std::string& geometryFilename, const std::string& fragmentFilename, const string& type) const
{
	multimap<string, ProgramSP>::const_iterator walker = allPrograms.begin();

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;

		if (currentProgram->getVertexFilename().compare(vertexFilename) == 0 && currentProgram->getControlFilename().compare(controlFilename) == 0 && currentProgram->getEvaluationFilename().compare(evaluationFilename) == 0 && currentProgram->getGeometryFilename().compare(geometryFilename) == 0 && currentProgram->getFragmentFilename().compare(fragmentFilename) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	currentProgram = ProgramSP(new Program(type, vertexFilename, controlFilename, evaluationFilename, geometryFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

const multimap<string, ProgramSP>& ProgramManager::getAllPrograms() const
{
	return allPrograms;
}

