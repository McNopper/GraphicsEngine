/*
 * GroundManager.cpp
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#include "GroundManager.h"

using namespace std;

GroundManager* GroundManager::instance;

GroundManager::GroundManager() :
		allGrounds()
{
}

GroundManager::~GroundManager()
{
	auto walker = allGrounds.begin();
	while (walker != allGrounds.end())
	{
		walker->second.reset();
		walker++;
	}
	allGrounds.clear();
}


GroundManager* GroundManager::getInstance()
{
	if (!instance)
	{
		instance = new GroundManager();
	}

	return instance;
}

void GroundManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

bool GroundManager::containsGroundByKey(const string& key) const
{
	return allGrounds.find(key) != allGrounds.end();
}

const GroundSP& GroundManager::getGroundByKey(const string& key) const
{
	return allGrounds.at(key);
}

void GroundManager::setGround(const string& key, const GroundSP& ground)
{
	allGrounds[key] = ground;
}

