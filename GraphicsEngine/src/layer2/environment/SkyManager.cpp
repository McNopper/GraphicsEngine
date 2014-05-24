/*
 * SkyManager.cpp
 *
 *  Created on: 18.11.2012
 *      Author: nopper
 */

#include "SkyManager.h"

using namespace std;

SkyManager::SkyManager() : Singleton<SkyManager>(), allSkies(), activeSky()
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
	SkySP foundSky = allSkies.search(key);

	if (!foundSky.get())
	{
		activeSky.reset();

		return;
	}

	activeSky = foundSky;
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
