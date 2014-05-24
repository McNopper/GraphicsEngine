/*
 * GroundManager.cpp
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#include "GroundManager.h"

using namespace std;

GroundManager::GroundManager() :
	Singleton<GroundManager>(), allGrounds()
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

bool GroundManager::containsGroundByKey(const string& key) const
{
	return allGrounds.contains(key);
}

const GroundSP& GroundManager::getGroundByKey(const string& key) const
{
	return allGrounds.at(key);
}

void GroundManager::setGround(const string& key, const GroundSP& ground)
{
	allGrounds[key] = ground;
}

