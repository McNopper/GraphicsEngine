/*
 * Matrix3x3.cpp
 *
 *  Created on: 23.04.2012
 *      Author: Norbert Nopper
 */

#include "Matrix4x4.h"

#include "Matrix3x3.h"

Matrix3x3::Matrix3x3()
{
	glusMatrix3x3Identityf(m);
}

Matrix3x3::Matrix3x3(const Matrix3x3& other)
{
	glusMatrix3x3Copyf(m, other.m, GLUS_FALSE);
}

Matrix3x3::Matrix3x3(const float other[9])
{
	glusMatrix3x3Copyf(m, other, GLUS_FALSE);
}

Matrix3x3::Matrix3x3(const Vector3& col0, const Vector3& col1, const Vector3& col2)
{
	glusMatrix3x3Initf(m, col0.v, col1.v, col2.v);
}

Matrix3x3::~Matrix3x3()
{

}

Matrix3x3 Matrix3x3::copy() const
{
	Matrix3x3 result;

	glusMatrix3x3Copyf(result.m, m, GLUS_FALSE);

	return result;
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& other)
{
	glusMatrix3x3Copyf(m, other.m, GLUS_FALSE);

	return *this;
}

Matrix4x4 Matrix3x3::createMatrix4x4() const
{
	Matrix4x4 result;

	glusMatrix3x3CreateMatrix4x4f(result.m, m);

	return result;
}

Vector3 Matrix3x3::operator*(const Vector3& v) const
{
	Vector3 result;

	glusMatrix3x3MultiplyVector3f(result.v, m, v.v);

	return result;
}

void Matrix3x3::identity()
{
	glusMatrix3x3Identityf(m);
}

bool Matrix3x3::inverse()
{
	return glusMatrix3x3Inversef(m) ? true : false;
}

void Matrix3x3::transpose()
{
	glusMatrix3x3Transposef(m);
}

void Matrix3x3::rotate(float angle, float x, float y, float z)
{
	glusMatrix3x3Rotatef(m, angle, x, y, z);
}

void Matrix3x3::rotateRzRyRx(float anglez, float angley, float anglex)
{
	glusMatrix3x3RotateRzRyRxf(m, anglez, angley, anglex);
}

void Matrix3x3::scale(float sx, float sy, float sz)
{
	glusMatrix3x3Scalef(m, sx, sy, sz);
}

void Matrix3x3::multiply(const Matrix3x3& other)
{
	glusMatrix3x3Multiplyf(m, m, other.m);
}

void Matrix3x3::setM(const float other[9])
{
	glusMatrix3x3Copyf(m, other, GLUS_FALSE);
}

const float* Matrix3x3::getM() const
{
	return m;
}

void Matrix3x3::setM(float value, int32_t index)
{
	m[index] = value;
}

float Matrix3x3::getM(int32_t index) const
{
	return m[index];
}

void Matrix3x3::debugOut() const
{
	glusLogPrint(GLUS_LOG_DEBUG, "Matrix3x3:");
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f", m[0], m[3], m[6]);
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f", m[1], m[4], m[7]);
	glusLogPrint(GLUS_LOG_DEBUG, "%f %f %f", m[2], m[5], m[8]);
}
