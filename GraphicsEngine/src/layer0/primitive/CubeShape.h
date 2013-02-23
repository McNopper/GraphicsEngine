/*
 * CubeShape.h
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#ifndef CUBESHAPE_H_
#define CUBESHAPE_H_

#include "Shape.h"

class CubeShape : public Shape
{

public:

	CubeShape(float halfExtend);
	virtual ~CubeShape();

};

#endif /* CUBESHAPE_H_ */
