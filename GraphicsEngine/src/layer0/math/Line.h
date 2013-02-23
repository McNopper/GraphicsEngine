/*
 * Line.h
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#ifndef LINE_H_
#define LINE_H_

#include "Point4.h"
#include "Vector3.h"

class Line
{

protected:

	Point4 point;
	Vector3 direction;

public:

	Line();
	Line(const Point4& point, const Vector3& direction);
	Line(const Line& other);
	~Line();

	float distance(const Point4& point) const;

};

#endif /* LINE_H_ */
