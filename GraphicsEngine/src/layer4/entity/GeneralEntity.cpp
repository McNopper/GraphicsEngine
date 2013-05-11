/*
 * GeneralEntity.cpp
 *
 *  Created on: 11.05.2013
 *      Author: nopper
 */

#include "GeneralEntity.h"

using namespace std;

using namespace boost;

float GeneralEntity::currentDeltaTime;
string GeneralEntity::currentProgramType;

void GeneralEntity::setCurrentValues(const string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder, enum RenderFilter renderFilter, bool dynamicCubeMaps)
{
	OctreeEntity::setCurrentValues(currentCamera, ascendingSortOrder, renderFilter, dynamicCubeMaps);
	GeneralEntity::currentProgramType = currentProgramType;
	GeneralEntity::currentDeltaTime = currentDeltaTime;
}

GeneralEntity::GeneralEntity() : OctreeEntity(), Geometry()
{
}

GeneralEntity::~GeneralEntity()
{
}

