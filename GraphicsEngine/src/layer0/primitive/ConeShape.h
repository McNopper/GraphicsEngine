/*
 * ConeShape.h
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#ifndef CONESHAPE_H_
#define CONESHAPE_H_

#include "Shape.h"

class ConeShape: public Shape
{

public:

	ConeShape(float halfExtend, float radius, boost::uint32_t numberSlices, boost::uint32_t numberStacks);
	virtual ~ConeShape();

};

#endif /* CONESHAPE_H_ */
