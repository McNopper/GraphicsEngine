/*
 * Quaternion.h
 *
 *  Created on: 02.05.2012
 *      Author: nopper
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector3.h"

class Quaternion {

private:

	float q[4];

	mutable Matrix4x4 rotationMatrix4x4;
	mutable Matrix3x3 rotationMatrix3x3;

	mutable bool dirtyFlag;

public:

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const float other[4]);
	Quaternion(const Quaternion& other);
	Quaternion(float angle, const Vector3& axis);
	Quaternion(const Matrix3x3& matrix);
	~Quaternion();

	bool operator ==(const Quaternion& other) const;
	bool operator !=(const Quaternion& other) const;

	Quaternion& operator*=(const Quaternion& other);

	Quaternion& operator =(const Quaternion& other);

	Quaternion operator *(const Quaternion& other) const;

	Vector3 operator *(const Vector3& vector) const;

	Point4 operator *(const Point4& point) const;

	Quaternion conjugate() const;

	void rotateRzRyRxf(const float anglez, const float angley, const float anglex);

	const Matrix4x4& getRotationMatrix4x4() const;

	const Matrix3x3& getRotationMatrix3x3() const;

	Quaternion slerp(const Quaternion& other, float t) const;

};

#endif /* QUATERNION_H_ */
