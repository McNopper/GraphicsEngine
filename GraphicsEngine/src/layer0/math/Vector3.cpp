/*
 * Vector3.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "Point4.h"

#include "Vector3.h"

using namespace std;

Vector3::Vector3()
{
	v[0] = 0.0f;
	v[1] = 1.0f;
	v[2] = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3::Vector3(const float other[3])
{
	v[0] = other[0];
	v[1] = other[1];
	v[2] = other[2];
}

Vector3::Vector3(const Vector3 & other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
}

Vector3::~Vector3()
{
}

float& Vector3::operator [](int32_t i)
{
	return v[i];
}

Vector3 Vector3::operator -() const
{
	return Vector3(-v[0], -v[1], -v[2]);
}

Vector3 Vector3::operator +(const Vector3& other) const
{
	Vector3 result;

	glusVector3AddVector3f(result.v, v, other.v);

	return result;
}

Vector3 Vector3::operator -(const Vector3& other) const
{
	Vector3 result;

	glusVector3SubtractVector3f(result.v, v, other.v);

	return result;
}

Vector3 Vector3::operator *(const Vector3& other) const
{
	return cross(other);
}

Vector3 Vector3::operator *(float scalar) const
{
	Vector3 result;

	glusVector3MultiplyScalarf(result.v, v, scalar);

	return result;
}

Vector3& Vector3::operator =(const Vector3& vector)
{
	v[0] = vector.v[0];
	v[1] = vector.v[1];
	v[2] = vector.v[2];

	return *this;
}

Vector3& Vector3::operator +=(const Vector3& vector)
{
	glusVector3AddVector3f(v, v, vector.v);

	return *this;
}

Vector3& Vector3::operator -=(const Vector3& vector)
{
	glusVector3SubtractVector3f(v, v, vector.v);

	return *this;
}

float Vector3::getX() const
{
	return v[0];
}

void Vector3::setX(float x)
{
	v[0] = x;
}

float Vector3::getY() const
{
	return v[1];
}

void Vector3::setY(float y)
{
	v[1] = y;
}

float Vector3::getZ() const
{
	return v[2];
}

void Vector3::setZ(float z)
{
	v[2] = z;
}

const float* Vector3::getV() const
{
	return v;
}

void Vector3::setV(float value, int32_t index)
{
	v[index] = value;
}

float Vector3::getV(int32_t index) const
{
	return v[index];
}

float Vector3::length() const
{
	return glusVector3Lengthf(v);
}

Vector3 Vector3::normalize() const
{
	Vector3 result(*this);

	glusVector3Normalizef(result.v);

	return result;
}

float Vector3::dot(const Vector3& other) const
{
	return glusVector3Dotf(v, other.v);
}

Vector3 Vector3::cross(const Vector3& other) const
{
	Vector3 result;

	glusVector3Crossf(result.v, v, other.v);

	return result;
}
