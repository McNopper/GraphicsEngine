/*
 * CylinderShape.h
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#ifndef CYLINDERSHAPE_H_
#define CYLINDERSHAPE_H_

#include "Shape.h"

class CylinderShape: public Shape
{

public:

	CylinderShape(float halfExtend, float radius, std::uint32_t numberSlices);
	virtual ~CylinderShape();

};

#endif /* CYLINDERSHAPE_H_ */
