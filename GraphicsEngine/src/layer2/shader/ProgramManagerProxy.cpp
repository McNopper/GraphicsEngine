/*
 * ProgramManagerProxy.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "../../layer0/shader/ProgramManager.h"

#include "ProgramManagerProxy.h"

using namespace std;

ProgramManagerProxy::ProgramManagerProxy()
{
}

ProgramManagerProxy::~ProgramManagerProxy()
{
}

void ProgramManagerProxy::setLightByType(const string& programType, const LightSP& light)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		light->setLightProperties(currentProgram);
		walker++;
	}
}

void ProgramManagerProxy::setCameraByType(const string& programType, const CameraSP& camera)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		camera->setCameraProperties(currentProgram);
		walker++;
	}
}

