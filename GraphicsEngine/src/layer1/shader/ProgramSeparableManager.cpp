/*
 * ProgramSeparableManager.cpp
 *
 *  Created on: 06.06.2014
 *      Author: nopper
 */

#include "ProgramSeparableManager.h"

using namespace std;

ProgramSeparableManager::ProgramSeparableManager() :
		Singleton<ProgramSeparableManager>(), allProgramSeparables()
{
}

ProgramSeparableManager::~ProgramSeparableManager()
{
}

void ProgramSeparableManager::addProgramSeparable(const ProgramSeparableSP& programSeparable)
{
	allProgramSeparables.add(programSeparable->getFilename(), programSeparable);
}

void ProgramSeparableManager::removeProgramSeparable(const ProgramSeparableSP& programSeparable)
{
	allProgramSeparables.remove(programSeparable->getFilename());
}

ProgramSeparableSP ProgramSeparableManager::getProgramSeparableBy(const string& filename) const
{
	return allProgramSeparables.search(filename);
}

const KeyValueMap<string, ProgramSeparableSP>& ProgramSeparableManager::getAllProgramSeparables() const
{
	return allProgramSeparables;
}
