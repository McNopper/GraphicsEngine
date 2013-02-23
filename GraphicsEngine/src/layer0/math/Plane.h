/*
 * Plane.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Point4.h"
#include "Sphere.h"
#include "Vector3.h"

class Plane
{

	friend class Matrix4x4;

protected:

	float plane[4];

public:

	Plane();
	Plane(const Point4& point, const Vector3& normal);
	Plane(const Vector3& normal, float d);
	Plane(const Plane& other);
	~Plane();

	Plane& operator =(const Plane& other);

	void setPlane(const Plane& other);

	void setPlane(const Vector3& normal, float d);

	const float* getPlane() const;

	float distance(const Point4& other) const;

	float distance(const Sphere& other) const;

};

#endif /* PLANE_H_ */
