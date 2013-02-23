/*
 * SkyManager.cpp
 *
 *  Created on: 18.11.2012
 *      Author: nopper
 */

#include "SkyManager.h"

using namespace std;

SkyManager* SkyManager::instance = nullptr;

SkyManager::SkyManager() : allSkies(), activeSky()
{
}

SkyManager::~SkyManager()
{
	activeSky.reset();

	auto walker = allSkies.begin();
	while (walker != allSkies.end())
	{
		walker->second.reset();
		walker++;
	}
	allSkies.clear();
}

SkyManager* SkyManager::getInstance()
{
	if (!instance)
	{
		instance = new SkyManager();
	}

	return instance;
}

void SkyManager::terminate()
{
	if (instance)
	{
		delete instance;

		instance = nullptr;
	}
}

const SkySP& SkyManager::getSky(const string& key) const
{
	return allSkies.at(key);
}

void SkyManager::setSky(const string& key, const SkySP& sky)
{
	allSkies[key] = sky;
}

const SkySP& SkyManager::getActiveSky() const
{
	return activeSky;
}

void SkyManager::setActiveSky(const string& key)
{
	auto foundSky = allSkies.find(key);

	if (foundSky == allSkies.end())
	{
		activeSky.reset();

		return;
	}

	activeSky = foundSky->second;
}

void SkyManager::resetActiveSky()
{
	activeSky.reset();
}

bool SkyManager::hasActiveSky() const
{
	return activeSky.get() != nullptr;
}

void SkyManager::setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const
{
	auto walker = allSkies.begin();
	while (walker != allSkies.end())
	{
		walker->second->setWriteBrightColor(writeBrightColor);
		walker->second->setBrightColorLimit(brightColorLimit);
		walker++;
	}
}
