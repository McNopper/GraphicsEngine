/*
 * ModelManager.cpp
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#include "ModelManager.h"

using namespace std;

ModelManager::ModelManager() :
	Singleton<ModelManager>(), allModels()
{
}

ModelManager::~ModelManager()
{
	map<string, ModelSP>::iterator walker = allModels.begin();
	while (walker != allModels.end())
	{
		walker->second.reset();
		walker++;
	}
	allModels.clear();
}

bool ModelManager::containsModelByKey(const string& key) const
{
	return allModels.contains(key);
}

const ModelSP& ModelManager::getModelByKey(const string& key) const
{
	return allModels.at(key);
}

void ModelManager::setModel(const string& key, const ModelSP& model)
{
	allModels[key] = model;
}
