/*
 * LineGeometryManager.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "LineGeometryManager.h"

using namespace std;

LineGeometryManager::LineGeometryManager() :
		Singleton<LineGeometryManager>()
{
}

LineGeometryManager::~LineGeometryManager() {
	auto walker = allLineGeometries.begin();
	while (walker != allLineGeometries.end())
	{
		walker->second.reset();
		walker++;
	}
	allLineGeometries.clear();
}

bool LineGeometryManager::containsLineGeometry(const string& key) const
{
	return allLineGeometries.find(key) != allLineGeometries.end();
}

const LineGeometrySP& LineGeometryManager::getLineGeometry(const string& key) const
{
	return allLineGeometries.at(key);
}

void LineGeometryManager::setLineGeometry(const string& key, const LineGeometrySP& lineGeometry)
{
	allLineGeometries[key] = lineGeometry;
}
