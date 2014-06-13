/*
 * SphereShape.h
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#ifndef SPHERESHAPE_H_
#define SPHERESHAPE_H_

#include "Shape.h"

class SphereShape : public Shape
{

public:

	SphereShape(float radius, std::uint32_t numberSlices);
	virtual ~SphereShape();

};

#endif /* SPHERESHAPE_H_ */
