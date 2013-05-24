/*
 * GroundPlane.cpp
 *
 *  Created on: 08.03.2013
 *      Author: nopper
 */

#include "DebugDraw.h"

#include "GroundPlane.h"

GroundPlane::GroundPlane() :
		plane(Point4(), Vector3(0.0f, 1.0f, 0.0f)), origin()
{
}

GroundPlane::GroundPlane(float elevation) :
	plane(Point4(0.0f, elevation, 0.0f), Vector3(0.0f, 1.0f, 0.0f)), origin()
{
}

GroundPlane::~GroundPlane()
{
}

void GroundPlane::draw(const Point4& eye, const Color& color) const
{
	origin.setX(ceilf(eye.getX()));
	origin.setZ(floorf(eye.getZ()));

	DebugDraw::drawer.draw(plane, origin, color);
}
