/*
 * Matrix3x3.h
 *
 *  Created on: 23.04.2012
 *      Author: Norbert Nopper
 */

#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_

#include "Vector3.h"

class Matrix4x4;

class Matrix3x3
{

	friend class Matrix4x4;
	friend class Quaternion;

protected:

	float m[9];

public:

	Matrix3x3();
	Matrix3x3(const Matrix3x3& other);
	Matrix3x3(const float other[9]);
	~Matrix3x3();

	Matrix3x3 copy() const;

	Matrix3x3& operator*=(const Matrix3x3& other);

	Matrix3x3 operator*(const Matrix3x3& other) const;

	Matrix4x4 createMatrix4x4() const;

	Vector3 operator*(const Vector3& v) const;

	void identity();

	bool inverse();

	void transpose();

	void rotate(float angle, float x, float y, float z);

	void rotateRzRyRx(float anglez, float angley, float anglex);

	void scale(float sx, float sy, float sz);

	void multiply(const Matrix3x3& other);

	void setM(const float other[9]);

	const float* getM() const;

	void debugOut() const;

};

#endif /* MATRIX3X3_H_ */
