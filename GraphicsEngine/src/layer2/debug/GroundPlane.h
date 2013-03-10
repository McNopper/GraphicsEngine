/*
 * GroundPlane.h
 *
 *  Created on: 08.03.2013
 *      Author: nopper
 */

#ifndef GROUNDPLANE_H_
#define GROUNDPLANE_H_

#include "../../layer0/math/Plane.h"
#include "../../layer0/math/Point4.h"

#include "../../UsedLibs.h"

class GroundPlane
{

private:

	Plane plane;
	mutable Point4 origin;

public:
	GroundPlane();
	GroundPlane(float elevation);
	virtual ~GroundPlane();

	void draw(const Point4& eye, const Color& color) const;

};

#endif /* GROUNDPLANE_H_ */
