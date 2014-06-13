/*
 * DomeShape.h
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#ifndef DOMESHAPE_H_
#define DOMESHAPE_H_

#include "Shape.h"

class DomeShape: public Shape
{
public:
	DomeShape(float radius, std::uint32_t numberSlices);
	virtual ~DomeShape();
};

#endif /* DOMESHAPE_H_ */
