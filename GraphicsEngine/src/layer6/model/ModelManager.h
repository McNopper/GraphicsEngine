/*
 * ModelManager.h
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#ifndef MODELMANAGER_H_
#define MODELMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Model.h"

class ModelManager : public Singleton<ModelManager>
{

	friend class Singleton<ModelManager>;

protected:

	KeyValueMap<std::string, ModelSP> allModels;

	ModelManager();
	virtual ~ModelManager();

public:

	bool containsModelByKey(const std::string& key) const;

	const ModelSP& getModelByKey(const std::string& key) const;

	void setModel(const std::string& key, const ModelSP& model);

};

#endif /* MODELMANAGER_H_ */
