/*
 * ViewportManager.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "ViewportManager.h"

using namespace std;

const string ViewportManager::DEFAULT_VIEWPORT_KEY = "default";

ViewportManager::ViewportManager() :
		Singleton<ViewportManager>(), allViewports()
{
	allViewports[DEFAULT_VIEWPORT_KEY] = ViewportSP(new Viewport(0, 0, 1, 1));
}

ViewportManager::~ViewportManager()
{
	map<string, ViewportSP>::iterator walker = allViewports.begin();
	while (walker != allViewports.end())
	{
		walker->second.reset();
		walker++;
	}
	allViewports.clear();
}

const ViewportSP& ViewportManager::getDefaultViewport() const
{
	return allViewports.at(DEFAULT_VIEWPORT_KEY);
}

bool ViewportManager::containsViewport(const string& key) const
{
	return allViewports.contains(key);
}

const ViewportSP& ViewportManager::getViewport(const string& key) const
{
	return allViewports.at(key);
}

void ViewportManager::setViewport(const string& key, const ViewportSP& viewport)
{
	assert(DEFAULT_VIEWPORT_KEY.compare(key) != 0);

	allViewports[key] = viewport;
}
