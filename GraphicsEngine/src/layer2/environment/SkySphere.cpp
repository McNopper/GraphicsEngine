/*
 * SkySphere.cpp
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#include "../../layer0/primitive/SphereShape.h"

#include "SkySphere.h"

using namespace std;

SkySphere::SkySphere(float radiusX, float radiusY, float radiusZ, const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ)
	: Sky(SphereShape(1.0f, 32), radiusX, radiusY, radiusZ, identifier, posX, negX, posY, negY, posZ, negZ)
{
}

SkySphere::SkySphere(float radiusX, float radiusY, float radiusZ, const string& filename)
	: Sky(SphereShape(1.0f, 32), radiusX, radiusY, radiusZ, filename)
{
}

SkySphere::~SkySphere()
{
}
