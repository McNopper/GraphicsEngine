/*
 * ProgramManagerProxy.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "../../layer1/shader/ProgramManager.h"
#include "../../layer3/light/LightManager.h"

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

void ProgramManagerProxy::setAmbientLightColorByType(const string& programType)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();
		glUniform4fv(currentProgram->getUniformLocation(u_ambientLightColor), 1, LightManager::getInstance()->getAmbientLightColor().getRGBA());
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

void ProgramManagerProxy::setNoShadowByType(const string& programType)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();

		for (int32_t i = 0; i < 8; i++)
		{
			glActiveTexture(GL_TEXTURE5 + i);
			glBindTexture(GL_TEXTURE_2D, 0);

			glUniform1i(currentProgram->getUniformLocation(string(u_shadowType) + to_string(i) + "]"), -1);
			glUniform1i(currentProgram->getUniformLocation(string(u_shadowTexture) + to_string(i) + "]"), 5 + i);

			glUniformMatrix4fv(currentProgram->getUniformLocation(string(u_shadowMatrix) + to_string(i) + "]"), 1, GL_FALSE, Matrix4x4().getM());
		}

		walker++;
	}
}

