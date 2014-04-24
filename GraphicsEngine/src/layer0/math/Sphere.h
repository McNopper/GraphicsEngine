/*
 * Sphere.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Plane.h"
#include "Point4.h"

class Sphere
{

protected:

	Point4 center;
	float radius;

public:

	Sphere();
	Sphere(const Point4& center, float radius);
	virtual ~Sphere();

    const Point4& getCenter() const;
    void setCenter(const Point4& center);

    float getRadius() const;
    void setRadius(float radius);

    float distance(const Point4& point) const;

    float distance(const Sphere& other) const;

	float distance(const Plane& other) const;

};

#endif /* SPHERE_H_ */
