/*
 * Matrix4x4.cpp
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#include "Matrix3x3.h"

#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	glusMatrix4x4Identityf(m);
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
{
	glusMatrix4x4Copyf(m, other.m, false);
}

Matrix4x4::Matrix4x4(const float other[16])
{
	glusMatrix4x4Copyf(m, other, false);
}

Matrix4x4::~Matrix4x4()
{

}

Matrix4x4 Matrix4x4::copy(bool rotationOnly) const
{
	Matrix4x4 result;

	glusMatrix4x4Copyf(result.m, m, rotationOnly);

	return result;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
	glusMatrix4x4Copyf(m, other.m, GLUS_FALSE);

	return *this;
}

Matrix3x3 Matrix4x4::extractMatrix3x3() const
{
	Matrix3x3 result;

	glusMatrix4x4ExtractMatrix3x3f(result.m, m);

	return result;
}

Vector3 Matrix4x4::operator*(const Vector3& v) const
{
	Vector3 result;

	glusMatrix4x4MultiplyVector3f(result.v, m, v.v);

	return result;
}

Point4 Matrix4x4::operator*(const Point4& p) const
{
	Point4 result;

	glusMatrix4x4MultiplyPoint4f(result.p, m, p.p);

	return result;
}

Plane Matrix4x4::operator*(const Plane& plane) const
{
	Plane result;

	glusMatrix4x4MultiplyPlanef(result.plane, m, plane.plane);

	return result;
}

void Matrix4x4::identity()
{
	glusMatrix4x4Identityf(m);
}

void Matrix4x4::inverseRigidBody()
{
	glusMatrix4x4InverseRigidBodyf(m);
}

void Matrix4x4::transpose()
{
	glusMatrix4x4Transposef(m);
}

void Matrix4x4::translate(float x, float y, float z)
{
	glusMatrix4x4Translatef(m, x, y, z);
}

void Matrix4x4::rotate(float angle, float x, float y, float z)
{
	glusMatrix4x4Rotatef(m, angle, x, y, z);
}

void Matrix4x4::rotateRzRyRx(float anglez, float angley, float anglex)
{
	glusMatrix4x4RotateRzRyRxf(m, anglez, angley, anglex);
}

void Matrix4x4::scale(float sx, float sy, float sz)
{
	glusMatrix4x4Scalef(m, sx, sy, sz);
}

void Matrix4x4::multiply(const Matrix4x4& other)
{
	glusMatrix4x4Multiplyf(m, m, other.m);
}

void Matrix4x4::setM(const float other[16])
{
	glusMatrix4x4Copyf(m, other, false);
}

const float* Matrix4x4::getM() const
{
	return m;
}

void Matrix4x4::setM(float value, int32_t index)
{
	m[index] = value;
}

float Matrix4x4::getM(int32_t index) const
{
	return m[index];
}

void Matrix4x4::debugOut() const
{
	glusLogPrint(GLUS_LOG_DEBUG, "Matrix4x4:");
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f %f", m[0], m[4], m[8], m[12]);
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f %f", m[1], m[5], m[9], m[13]);
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f %f", m[2], m[6], m[10], m[14]);
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f %f", m[3], m[7], m[11], m[15]);
}
