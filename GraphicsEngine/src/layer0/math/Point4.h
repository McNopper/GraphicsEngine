/*
 * Point4.h
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#ifndef POINT4_H_
#define POINT4_H_

#include "../../UsedLibs.h"

class Line;
class Plane;
class Sphere;
class Vector3;

class Point4
{

	friend class Matrix4x4;
	friend class Vector3;

private:

	float p[4];

public:

	Point4();
	Point4(float x, float y, float z);
	Point4(const float other[4]);
	Point4(const Point4& other);
	~Point4();

	float& operator [](std::int32_t i);

	bool operator ==(const Point4& other) const;
	bool operator !=(const Point4& other) const;

	Point4 operator +(const Vector3& vector) const;
	Point4 operator -(const Vector3& vector) const;

	Point4& operator +=(const Vector3& vector);
	Point4& operator -=(const Vector3& vector);

	Point4& operator =(const Point4& other);

	Vector3 operator -(const Point4& other) const;

	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	float getZ() const;
	void setZ(float z);
	float getW() const;

	const float* getP() const;

	float distance(const Point4& other) const;

	float distance(const Line& line) const;

	float distance(const Plane& plane) const;

	float distance(const Sphere& sphere) const;

	Point4 lerp(const Point4& other, float t) const;

};

#endif /* POINT4_H_ */
