/*
 * DebugDraw.h
 *
 *  Created on: 17.09.2012
 *      Author: nopper
 */

#ifndef DEBUGDRAW_H_
#define DEBUGDRAW_H_

#include "../../layer0/color/Color.h"
#include "../../layer0/math/AxisAlignedBox.h"
#include "../../layer0/math/Plane.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Sphere.h"

class DebugDraw
{

private:

	DebugDraw();
	virtual ~DebugDraw();

public:

	static const DebugDraw drawer;

	void draw(const Point4& start, const Point4& end, const Color& color) const;

	void draw(const Sphere& Sphere, const Color& color, bool mesh = false) const;

	void draw(const AxisAlignedBox& axisAlignedBox, const Color& color) const;

	void draw(const Plane& plane, const Point4& origin, const Color& color) const;

};

#endif /* DEBUGDRAW_H_ */
