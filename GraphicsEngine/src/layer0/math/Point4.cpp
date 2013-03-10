/*
 * Point4.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "Line.h"
#include "Plane.h"
#include "Sphere.h"
#include "Vector3.h"

#include "Point4.h"

Point4::Point4()
{
	p[0] = 0.0f;
	p[1] = 0.0f;
	p[2] = 0.0f;
	p[3] = 1.0f;
}

Point4::Point4(float x, float y, float z)
{
	p[0] = x;
	p[1] = y;
	p[2] = z;
	p[3] = 1.0f;
}

Point4::Point4(const float other[4])
{
	p[0] = other[0];
	p[1] = other[1];
	p[2] = other[2];
	p[3] = other[3];
}

Point4::Point4(const Point4 & other)
{
	p[0] = other.p[0];
	p[1] = other.p[1];
	p[2] = other.p[2];
	p[3] = other.p[3];
}

Point4::~Point4()
{
}

Point4 Point4::operator +(const Vector3& vector) const
{
	Point4 result;

	glusPoint4AddVector3f(result.p, p, vector.v);

	return result;
}

Point4 Point4::operator -(const Vector3& vector) const
{
	Point4 result;

	glusPoint4SubtractVector3f(result.p, p, vector.v);

	return result;
}

Point4& Point4::operator +=(const Vector3& vector)
{
	glusPoint4AddVector3f(p, p, vector.v);

	return *this;
}

Point4& Point4::operator -=(const Vector3& vector)
{
	glusPoint4SubtractVector3f(p, p, vector.v);

	return *this;
}

Vector3 Point4::operator -(const Point4 & other) const
{
	Vector3 result;

	glusPoint4SubtractPoint4f(result.v, p, other.p);

	return result;
}

float Point4::getX() const
{
	return p[0];
}

void Point4::setX(float x)
{
	p[0] = x;
}

float Point4::getY() const
{
	return p[1];
}

void Point4::setY(float y)
{
	p[1] = y;
}

float Point4::getZ() const
{
	return p[2];
}

void Point4::setZ(float z)
{
	p[2] = z;
}

float Point4::getW() const
{
	return p[3];
}

void Point4::setW(float w)
{
	p[3] = w;
}

const float* Point4::getP() const
{
	return p;
}

float Point4::distance(const Point4 & other) const
{
	Vector3 result = *this - other;

	return result.length();
}

float Point4::distance(const Line& line) const
{
	return line.distance(*this);
}

float Point4::distance(const Plane& plane) const
{
	return plane.distance(*this);
}

float Point4::distance(const Sphere& sphere) const
{
	return sphere.distance(*this);
}
