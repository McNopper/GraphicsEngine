/*
 * ModelPersistence.h
 *
 *  Created on: 28.02.2014
 *      Author: nopper
 */

#ifndef MODELPERSISTENCE_H_
#define MODELPERSISTENCE_H_

#include "../../UsedLibs.h"

#include "Model.h"

class ModelPersistence
{
public:
	ModelPersistence();
	virtual ~ModelPersistence();

	bool saveModel(const std::string& filename, const ModelSP& model) const;
};

#endif /* MODELPERSISTENCE_H_ */
