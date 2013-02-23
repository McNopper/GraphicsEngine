/*
 * ModelManager.h
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#ifndef MODELMANAGER_H_
#define MODELMANAGER_H_

#include "../../UsedLibs.h"

#include "Model.h"

class ModelManager
{

private:

	static ModelManager* instance;

	std::map<std::string, ModelSP> allModels;

private:

	ModelManager();
	virtual ~ModelManager();

public:

	static ModelManager* getInstance();

	static void terminate();

	bool containsModelByKey(const std::string& key) const;

	const ModelSP& getModelByKey(const std::string& key) const;

	void setModel(const std::string& key, const ModelSP& model);

};

#endif /* MODELMANAGER_H_ */
