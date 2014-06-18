/*
 * GlTfEntityFactory.cpp
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#include "GlTfEntityFactory.h"

using namespace std;

GlTfEntityFactory::GlTfEntityFactory()
{
}

GlTfEntityFactory::~GlTfEntityFactory()
{
}

bool GlTfEntityFactory::saveGlTfModelFile(const ModelEntitySP& modelEntity, const string& identifier)
{
	if (modelEntity.get() == nullptr)
	{
		return false;
	}

	// TODO Go through model entity and create glTF / JSON objects. Save as JSON text.

	return true;
}
