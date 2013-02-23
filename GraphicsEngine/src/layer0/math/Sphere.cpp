/*
 * Sphere.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "Sphere.h"

Sphere::Sphere() :
	center(), radius(0.0f)
{
}

Sphere::Sphere(const Point4& center, float radius) :
	center(center), radius(radius)
{
}

Sphere::~Sphere()
{
}

const Point4& Sphere::getCenter() const
{
	return center;
}

void Sphere::setCenter(const Point4& center)
{
	this->center = center;
}

float Sphere::getRadius() const
{
	return radius;
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

float Sphere::distance(const Point4& point) const
{
	return center.distance(point);
}

float Sphere::distance(const Sphere& other) const
{
	return center.distance(other.center);
}

float Sphere::distance(const Plane& other) const
{
	return other.distance(*this);
}
