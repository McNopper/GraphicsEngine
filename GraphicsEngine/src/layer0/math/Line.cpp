/*
 * Line.cpp
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "Line.h"

Line::Line() :
	point(), direction()
{
}

Line::Line(const Point4& point, const Vector3& direction) :
	point(point)
{
	this->direction = direction.normalize();
}

Line::Line(const Line& other) :
	point(other.point), direction(other.direction)
{
}

Line::~Line()
{
}

float Line::distance(const Point4& point) const
{
	Vector3 v = point - this->point;

	float c = v.length();

	float a = v.dot(direction);

	return sqrtf(c * c - a * a);
}
