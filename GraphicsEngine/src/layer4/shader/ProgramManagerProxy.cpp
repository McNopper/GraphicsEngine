/*
 * ProgramManagerProxy.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "../../layer1/shader/ProgramManager.h"

#include "ProgramManagerProxy.h"

using namespace boost;

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
		glUniform1i(currentProgram->getUniformLocation(u_numberLights), 1);
		light->setLightProperties(0, currentProgram);
		walker++;
	}
}

void ProgramManagerProxy::setLightsByType(const std::string& programType, const std::vector<LightSP>& lights)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		glUniform1i(currentProgram->getUniformLocation(u_numberLights), static_cast<int32_t>(lights.size()));

		for (uint32_t i = 0; i < lights.size(); i++)
		{
			lights[i]->setLightProperties(i, currentProgram);
		}
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

