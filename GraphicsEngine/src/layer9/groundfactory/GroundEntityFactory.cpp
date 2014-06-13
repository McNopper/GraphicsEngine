/*
 * GroundEntityFactory.cpp
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#include "../../layer2/ground/GroundFactory.h"
#include "../../layer2/ground/GroundManager.h"

#include "GroundEntityFactory.h"

using namespace std;

GroundEntityFactory::GroundEntityFactory()
{
}

GroundEntityFactory::~GroundEntityFactory()
{
}

GroundEntitySP GroundEntityFactory::createGroundEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	GroundFactory groundFactory;

	uint32_t rows = static_cast<uint32_t>(2.0f * scaleY);
	uint32_t columns = static_cast<uint32_t>(2.0f * scaleX);

	if (rows == 0)
	{
		rows = 1;
	}
	if (columns == 0)
	{
		columns = 1;
	}

	if (GroundManager::getInstance()->containsGroundByKey(name))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Ground '%s' already exists!", name.c_str());

		return GroundEntitySP();
	}

	GroundSP ground = groundFactory.createGround(1.0f, 1.0f, rows, columns);
	GroundManager::getInstance()->setGround(name, ground);

	return GroundEntitySP(new GroundEntity(name, ground, surfaceMaterial, scaleX, scaleY, scaleZ));
}
