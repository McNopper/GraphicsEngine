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

void ProgramManagerProxy::setLightByType(const string& programType, int32_t index, const LightSP& light, const Point4& position, const Quaternion& rotation)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		light->setLightProperties(index, currentProgram, position, rotation);
		walker++;
	}
}

void ProgramManagerProxy::setNumberLightsByType(const std::string& programType, boost::int32_t numberLights)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		glUniform1i(currentProgram->getUniformLocation(u_numberLights), numberLights);
		walker++;
	}
}

void ProgramManagerProxy::setCameraByType(const string& programType, const CameraSP& camera, const Point4& position, const Quaternion& rotation, bool useLocation)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		camera->setCameraProperties(currentProgram, position, rotation, useLocation);
		walker++;
	}
}

