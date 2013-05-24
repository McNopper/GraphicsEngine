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
#include "../../layer0/math/Quaternion.h"
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

	void drawSphere(const Point4& position, const Vector3& offset, float radius, const Color& color) const;

	void drawCone(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfExtend, float radius, const Color& color) const;

	void drawCylinder(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfExtend, float radius, const Color& color) const;

	void drawArrow(const Point4& position, const Vector3& offset, const Quaternion& rotation, float lengthTail, float radiusTail, float lengthHead, float radiusHead, const Color& color) const;

	void drawPyramid(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfWidth, float halfDepth, float halfHeight, const Color& color) const;

};

#endif /* DEBUGDRAW_H_ */
