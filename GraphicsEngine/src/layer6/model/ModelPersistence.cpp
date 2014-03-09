/*
 * ModelPersistence.cpp
 *
 *  Created on: 28.02.2014
 *      Author: nopper
 */

#include "ModelPersistence.h"

using namespace std;

ModelPersistence::ModelPersistence()
{
}

ModelPersistence::~ModelPersistence()
{
}

bool ModelPersistence::saveModel(const string& filename, const ModelSP& model) const
{
	if (!model.get())
	{
		return false;
	}

	if (!filename.c_str())
	{
		return false;
	}

	FILE* f;

	f = fopen(filename.c_str(), "w");

	if (!f)
	{
		return false;
	}

	bool result = model->saveModel(f);

	fclose(f);

	return result;
}
