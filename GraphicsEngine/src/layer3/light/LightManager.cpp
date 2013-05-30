/*
 * LightManager.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "DirectionalLight.h"

#include "LightManager.h"

using namespace std;

const string LightManager::DEFAULT_DIRECTIONAL_LIGHT_KEY = "default_directional";

LightManager* LightManager::instance;

LightManager::LightManager() : allLights()
{
	Color ambient(0.1f, 0.1f, 0.1f, 1.0f);
	Color specular(0.1f, 0.1f, 0.1f, 1.0f);

	allLights[DEFAULT_DIRECTIONAL_LIGHT_KEY] = LightSP(new DirectionalLight(DEFAULT_DIRECTIONAL_LIGHT_KEY, ambient, Color::WHITE, specular));
}

LightManager::~LightManager()
{
	auto walker = allLights.begin();
	while (walker != allLights.end())
	{
		walker->second.reset();
		walker++;
	}
	allLights.clear();
}

LightManager* LightManager::getInstance()
{
	if (!instance)
	{
		instance = new LightManager();
	}

	return instance;
}

void LightManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

bool LightManager::containsLight(const string& key) const
{
	return allLights.find(key) != allLights.end();
}

const LightSP& LightManager::getLight(const string& key) const
{
	return allLights.at(key);
}

const LightSP& LightManager::getDefaultDirectionalLight() const
{
	return allLights.at(DEFAULT_DIRECTIONAL_LIGHT_KEY);
}

void LightManager::setLight(const string& key, const LightSP& light)
{
	allLights[key] = light;

	glusLogPrint(GLUS_LOG_INFO, "Adding light to manager: %s", light->getName().c_str());
}




