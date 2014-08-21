/*
 * Plane.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "Plane.h"

Plane::Plane()
{
	plane[0] = 0.0f;
	plane[1] = 1.0f;
	plane[2] = 0.0f;
	plane[3] = 0.0f;
}

Plane::Plane(const Point4& point, const Vector3& normal)
{
	glusPlaneCreatef(plane, point.getP(), normal.getV());
}

Plane::Plane(const Vector3& normal, float d)
{
	setPlane(normal, d);
}

Plane::Plane(const Plane& other)
{
	setPlane(other);
}

Plane::~Plane()
{
}

Plane& Plane::operator =(const Plane& other)
{
	setPlane(other);

	return *this;
}

void Plane::setPlane(const Plane& other)
{
	plane[0] = other.plane[0];
	plane[1] = other.plane[1];
	plane[2] = other.plane[2];
	plane[3] = other.plane[3];

	float length = glusMathLengthf(plane[0], plane[1], plane[2]);

	if (length != 0.0f)
	{
		plane[0] /= length;
		plane[1] /= length;
		plane[2] /= length;
		plane[3] /= length;
	}
}

void Plane::setPlane(const Vector3& normal, float d)
{
	plane[0] = normal.v[0];
	plane[1] = normal.v[1];
	plane[2] = normal.v[2];
	plane[3] = d;

	float length = glusMathLengthf(plane[0], plane[1], plane[2]);

	if (length != 0.0f)
	{
		plane[0] /= length;
		plane[1] /= length;
		plane[2] /= length;
		plane[3] /= length;
	}
}

const float* Plane::getPlane() const
{
	return plane;
}

float Plane::distance(const Point4& other) const
{
	return glusPlaneDistancePoint4f(plane, other.getP());
}

float Plane::distance(const Sphere& other) const
{
	return distance(other.getCenter());
}
