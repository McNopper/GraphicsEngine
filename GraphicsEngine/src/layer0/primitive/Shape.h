/*
 * Shape.h
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "../../UsedLibs.h"

class Shape
{

protected:

	GLUSshape shape;

public:

	Shape();
	Shape(const GLUSshape& shape);
	virtual ~Shape();

	Shape& operator =(const Shape& other);

	const GLUSshape& getShape() const;
};

#endif /* SHAPE_H_ */
