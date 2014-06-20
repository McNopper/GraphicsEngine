/*
 * GlTfEntityFactory.h
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYFACTORY_H_
#define GLTFENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/json/JSONobject.h"
#include "../../layer0/json/JSONstring.h"
#include "../../layer8/modelentity/ModelEntity.h"

class GlTfEntityFactory
{

private:

	void addSampler(JSONobjectSP& samplersObject, const JSONstringSP& key, const Texture2DSP& texture) const;

	void addImage(JSONobjectSP& imagesObject, const JSONstringSP& key, const Texture2DSP& texture) const;

	void addTexture(JSONobjectSP& texturesObject, const JSONstringSP& key, const Texture2DSP& texture) const;

public:

	GlTfEntityFactory();
	virtual ~GlTfEntityFactory();

	bool saveGlTfModelFile(const ModelEntitySP& modelEntity, const std::string& identifier);

};

#endif /* GLTFENTITYFACTORY_H_ */
