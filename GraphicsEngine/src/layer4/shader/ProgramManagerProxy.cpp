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

void ProgramManagerProxy::setNumberLightsByType(const std::string& programType, std::int32_t numberLights)
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

		for (int32_t i = 0; i < 4; i++)
		{
			glActiveTexture(GL_TEXTURE5 + i);
			glBindTexture(GL_TEXTURE_2D, 0);

			glUniform1i(currentProgram->getUniformLocation(string(u_shadowType) + to_string(i) + "]"), -1);
			glUniform1i(currentProgram->getUniformLocation(string(u_shadowTexture) + to_string(i) + "]"), 5 + i);
			glUniform1f(currentProgram->getUniformLocation(string(u_shadowSections) + to_string(i) + "]"), 1.0f);

			for (int32_t k = 0; k < 3; k++)
			{
				glUniformMatrix4fv(currentProgram->getUniformLocation(string(u_shadowMatrix) + to_string((i * 4 + k)) + "]"), 1, GL_FALSE, Matrix4x4().getM());
			}
		}

		walker++;
	}
}

void ProgramManagerProxy::setShadowByType(const string& programType, int32_t index, const ShadowMap2DSP& shadowMap, const Matrix4x4& shadowMatrix, int32_t shadowType)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();

		glActiveTexture(GL_TEXTURE5 + index);
		glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap->getDepthTextureName());

		glUniform1i(currentProgram->getUniformLocation(string(u_shadowType) + to_string(index) + "]"), shadowType);
		glUniform1i(currentProgram->getUniformLocation(string(u_shadowTexture) + to_string(index) + "]"), 5 + index);
		glUniform1f(currentProgram->getUniformLocation(string(u_shadowSections) + to_string(index) + "]"), 1.0f);

		for (int32_t k = 0; k < 3; k++)
		{
			glUniformMatrix4fv(currentProgram->getUniformLocation(string(u_shadowMatrix) + to_string(index * 4 + k) + "]"), 1, GL_FALSE, shadowMatrix.getM());
		}

		walker++;
	}
}

void ProgramManagerProxy::setCascadedShadowByType(const string& programType, int32_t index, const ShadowMap2DSP& shadowMap, const vector<Matrix4x4>& shadowMatrices, int32_t shadowType)
{
	auto allPrograms = ProgramManager::getInstance()->getAllPrograms();

	multimap<string, ProgramSP>::const_iterator walker = allPrograms.find(programType);

	ProgramSP currentProgram;
	while (walker != allPrograms.end())
	{
		currentProgram = walker->second;
		currentProgram->use();

		glActiveTexture(GL_TEXTURE5 + index);
		glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap->getDepthTextureName());

		glUniform1i(currentProgram->getUniformLocation(string(u_shadowType) + to_string(index) + "]"), shadowType);
		glUniform1i(currentProgram->getUniformLocation(string(u_shadowTexture) + to_string(index) + "]"), 5 + index);
		glUniform1f(currentProgram->getUniformLocation(string(u_shadowSections) + to_string(index) + "]"), static_cast<float>(shadowMatrices.size()));

		for (int32_t k = 0; k < 3; k++)
		{
			if (k < static_cast<int32_t>(shadowMatrices.size()))
			{
				glUniformMatrix4fv(currentProgram->getUniformLocation(string(u_shadowMatrix) + to_string(index * 4 + k) + "]"), 1, GL_FALSE, shadowMatrices[k].getM());
			}
			else
			{
				glUniformMatrix4fv(currentProgram->getUniformLocation(string(u_shadowMatrix) + to_string(index * 4 + k) + "]"), 1, GL_FALSE, shadowMatrices[shadowMatrices.size()-1].getM());
			}
		}

		walker++;
	}
}
