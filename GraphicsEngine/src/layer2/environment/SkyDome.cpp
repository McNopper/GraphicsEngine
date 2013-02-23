/*
 * SkyDome.cpp
 *
 *  Created on: 11.11.2012
 *      Author: nopper
 */

#include "../../layer0/primitive/DomeShape.h"

#include "SkyDome.h"

using namespace std;

SkyDome::SkyDome(float radiusX, float radiusY, float radiusZ, const string& filename)
: Sky(DomeShape(1.0f, 32), radiusX, radiusY, radiusZ, filename)
{
}

SkyDome::~SkyDome()
{
}

