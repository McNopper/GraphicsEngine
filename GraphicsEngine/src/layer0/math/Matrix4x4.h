/*
 * Matrix4x4.h
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include "../../UsedLibs.h"

#include "Plane.h"
#include "Point4.h"
#include "Vector3.h"

class Matrix3x3;

class Matrix4x4
{

	friend class Matrix3x3;
	friend class Quaternion;

protected:

	float m[16];

public:

	Matrix4x4();
	Matrix4x4(const Matrix4x4& other);
	Matrix4x4(const float other[16]);
	~Matrix4x4();

	Matrix4x4 copy(bool rotationOnly = false) const;

	Matrix4x4& operator=(const Matrix4x4& other);

	Matrix4x4& operator*=(const Matrix4x4& other)
	{
		glusMatrix4x4Multiplyf(m, m, other.m);

		return *this;
	}

	Matrix4x4 operator*(const Matrix4x4& other) const
	{
		Matrix4x4 result;

		glusMatrix4x4Multiplyf(result.m, m, other.m);

		return result;
	}

	Matrix3x3 extractMatrix3x3() const;

	Vector3 operator*(const Vector3& v) const;

	Point4 operator*(const Point4& p) const;

	Plane operator*(const Plane& plane) const;

	void identity();

	void inverseRigidBody();

	void transpose();

	void translate(float x, float y, float z);

	void rotate(float angle, float x, float y, float z);

	void rotateRzRyRx(float anglez, float angley, float anglex);

	void scale(float sx, float sy, float sz);

	void multiply(const Matrix4x4& other);

	void setM(const float other[16]);

	const float* getM() const;

	void setM(float value, std::int32_t index);

	float getM(std::int32_t index) const;

	void debugOut() const;

};

#endif /* MATRIX4X4_H_ */
