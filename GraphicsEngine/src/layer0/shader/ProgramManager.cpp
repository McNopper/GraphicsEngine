/*
 * ProgramManager.cpp
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#include "Variables.h"

#include "ProgramManager.h"

using namespace std;

ProgramManager* ProgramManager::instance;

const string ProgramManager::DEFAULT_PROGRAM_TYPE = "default";

ProgramManager::ProgramManager() :
	allPrograms()
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

ProgramManager* ProgramManager::getInstance()
{
	if (!instance)
	{
		instance = new ProgramManager();
	}

	return instance;
}

void ProgramManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
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

ProgramSP ProgramManager::getProgramBy(const string& computeFilename) const
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

	currentProgram
			= ProgramSP(new Program(ProgramManager::DEFAULT_PROGRAM_TYPE, computeFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getProgramBy(const string& vertexFilename, const string& fragmentFilename) const
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

	currentProgram
			= ProgramSP(new Program(ProgramManager::DEFAULT_PROGRAM_TYPE, vertexFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getProgramBy(const string& vertexFilename, const string& geometryFilename, const string& fragmentFilename) const
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

	currentProgram
			= ProgramSP(new Program(ProgramManager::DEFAULT_PROGRAM_TYPE, vertexFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

ProgramSP ProgramManager::getProgramBy(const std::string& vertexFilename, const std::string& controlFilename, const std::string& evaluationFilename, const std::string& geometryFilename, const std::string& fragmentFilename) const
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

	currentProgram
			= ProgramSP(new Program(ProgramManager::DEFAULT_PROGRAM_TYPE, vertexFilename, fragmentFilename));

	ProgramManager::getInstance()->addProgram(currentProgram);

	return currentProgram;
}

const multimap<string, ProgramSP>& ProgramManager::getAllPrograms() const
{
	return allPrograms;
}

