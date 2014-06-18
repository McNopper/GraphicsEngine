/*
 * GlTfEntityFactory.h
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYFACTORY_H_
#define GLTFENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer8/modelentity/ModelEntity.h"

class GlTfEntityFactory
{

public:

	GlTfEntityFactory();
	virtual ~GlTfEntityFactory();

	bool saveGlTfModelFile(const ModelEntitySP& modelEntity, const std::string& identifier);

};

#endif /* GLTFENTITYFACTORY_H_ */
