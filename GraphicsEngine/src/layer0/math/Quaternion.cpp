/*
 * Quaternion.cpp
 *
 *  Created on: 02.05.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "Quaternion.h"

Quaternion::Quaternion() :
	dirtyFlag(true)
{
	glusQuaternionIdentityf(q);
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	dirtyFlag(true)
{
	q[0] = x;
	q[1] = y;
	q[2] = z;
	q[3] = w;
}

Quaternion::Quaternion(const float other[4]) :
	dirtyFlag(true)
{
	q[0] = other[0];
	q[1] = other[1];
	q[2] = other[2];
	q[3] = other[3];
}

Quaternion::Quaternion(const Quaternion& other) :
	dirtyFlag(true)
{
	q[0] = other.q[0];
	q[1] = other.q[1];
	q[2] = other.q[2];
	q[3] = other.q[3];
}

Quaternion::Quaternion(float angle, const Vector3& axis) :
	dirtyFlag(true)
{
	glusQuaternionRotatef(q, angle, axis.getX(), axis.getY(), axis.getZ());
}

Quaternion::Quaternion(const Matrix3x3& matrix) :
	dirtyFlag(true)
{
	float angles[3];

	glusQuaternionIdentityf(q);

	glusMatrix3x3GetEulerRzRyRxf(angles, matrix.m);

	glusQuaternionRotateRzRyRxf(q, angles[2], angles[1], angles[0]);
}

Quaternion::~Quaternion()
{
}

bool Quaternion::operator ==(const Quaternion& other) const
{
	for (int32_t i = 0; i < 4; i++)
	{
		if (q[i] != other.q[i])
		{
			return false;
		}
	}

	return true;
}

bool Quaternion::operator !=(const Quaternion& other) const
{
	return !(*this == other);
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	glusQuaternionMultiplyQuaternionf(q, q, other.q);

	return *this;
}

Quaternion& Quaternion::operator =(const Quaternion& other)
{
	q[0] = other.q[0];
	q[1] = other.q[1];
	q[2] = other.q[2];
	q[3] = other.q[3];

	// Do not copy the matrix. Will be updated when getting it.

	dirtyFlag = true;

	return *this;
}

Quaternion Quaternion::operator *(const Quaternion& other) const
{
	Quaternion result;

	glusQuaternionMultiplyQuaternionf(result.q, q, other.q);

	return result;
}

Vector3 Quaternion::operator *(const Vector3& vector) const
{
	Quaternion result = (*this) * Quaternion(vector.getX(), vector.getY(), vector.getZ(), 0.0f) * conjugate();

	return Vector3(result.q[0], result.q[1], result.q[2]);
}

Point4 Quaternion::operator *(const Point4& point) const
{
	Quaternion result = (*this) * Quaternion(point.getX(), point.getY(), point.getZ(), 0.0f) * conjugate();

	return Point4(result.q[0], result.q[1], result.q[2]);
}

Quaternion Quaternion::conjugate() const
{
	Quaternion result(*this);

	glusQuaternionConjugatef(result.q);

	return result;
}

void Quaternion::rotateRzRyRxf(const float anglez, const float angley, const float anglex)
{
	glusQuaternionRotateRzRyRxf(q, anglez, angley, anglex);
}

const Matrix4x4& Quaternion::getRotationMatrix4x4() const
{
	if (dirtyFlag)
	{
		glusQuaternionGetMatrix4x4f(rotationMatrix4x4.m, q);
		glusQuaternionGetMatrix3x3f(rotationMatrix3x3.m, q);

		dirtyFlag = false;
	}

	return rotationMatrix4x4;
}

const Matrix3x3& Quaternion::getRotationMatrix3x3() const
{
	if (dirtyFlag)
	{
		glusQuaternionGetMatrix4x4f(rotationMatrix4x4.m, q);
		glusQuaternionGetMatrix3x3f(rotationMatrix3x3.m, q);

		dirtyFlag = false;
	}

	return rotationMatrix3x3;
}

Quaternion Quaternion::slerp(const Quaternion& other, float t) const
{
	Quaternion result;

	glusQuaternionSlerpf(result.q, q, other.q, t);

	return result;
}
