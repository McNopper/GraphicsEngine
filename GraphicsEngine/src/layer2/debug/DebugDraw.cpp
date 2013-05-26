/*
 * DebugDraw.cpp
 *
 *  Created on: 17.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "LineGeometry.h"
#include "LineGeometryManager.h"

#include "DebugDraw.h"

const DebugDraw DebugDraw::drawer = DebugDraw();

DebugDraw::DebugDraw()
{
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::draw(const Point4& start, const Point4& end, const Color& color) const
{
	if (!LineGeometryManager::getInstance()->getLineGeometry("SingleLine").get())
	{
		return;
	}

	LineGeometryManager::getInstance()->getLineGeometry("SingleLine")->drawLines(Matrix4x4(), start, end, color);
}

void DebugDraw::draw(const Sphere& sphere, const Color& color, bool mesh) const
{
	Matrix4x4 modelMatrix;

	if (mesh)
	{
		if (!LineGeometryManager::getInstance()->getLineGeometry("Sphere").get())
		{
			return;
		}

		modelMatrix.identity();
		modelMatrix.translate(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
		modelMatrix.scale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		glDisable(GL_CULL_FACE);
		LineGeometryManager::getInstance()->getLineGeometry("Sphere")->draw(modelMatrix, color);
		glEnable(GL_CULL_FACE);
	}
	else
	{
		if (!LineGeometryManager::getInstance()->getLineGeometry("Circle").get())
		{
			return;
		}

		modelMatrix.identity();
		modelMatrix.translate(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
		modelMatrix.rotateRzRyRx(0.0f, 0.0f, 0.0f);
		modelMatrix.scale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		LineGeometryManager::getInstance()->getLineGeometry("Circle")->draw(modelMatrix, color);

		modelMatrix.identity();
		modelMatrix.translate(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
		modelMatrix.rotateRzRyRx(0.0f, 90.0f, 0.0f);
		modelMatrix.scale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		LineGeometryManager::getInstance()->getLineGeometry("Circle")->draw(modelMatrix, color);

		modelMatrix.identity();
		modelMatrix.translate(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
		modelMatrix.rotateRzRyRx(0.0f, 0.0f, 90.0f);
		modelMatrix.scale(sphere.getRadius(), sphere.getRadius(), sphere.getRadius());
		LineGeometryManager::getInstance()->getLineGeometry("Circle")->draw(modelMatrix, color);
	}
}

void DebugDraw::draw(const AxisAlignedBox& axisAlignedBox, const Color& color) const
{
	if (!LineGeometryManager::getInstance()->getLineGeometry("Square").get())
	{
		return;
	}

	Matrix4x4 modelMatrix;

	// Front
	modelMatrix.identity();
	modelMatrix.translate(axisAlignedBox.getCenter().getX(), axisAlignedBox.getCenter().getY(), axisAlignedBox.getCenter().getZ());
	modelMatrix.translate(0.0f, 0.0f, axisAlignedBox.getHalfDepth());
	modelMatrix.rotateRzRyRx(0.0f, 0.0f, 0.0f);
	modelMatrix.scale(axisAlignedBox.getHalfWidth(), axisAlignedBox.getHalfHeight(), 0.0f);
	LineGeometryManager::getInstance()->getLineGeometry("Square")->draw(modelMatrix, color);

	// Back
	modelMatrix.identity();
	modelMatrix.translate(axisAlignedBox.getCenter().getX(), axisAlignedBox.getCenter().getY(), axisAlignedBox.getCenter().getZ());
	modelMatrix.translate(0.0f, 0.0f, -axisAlignedBox.getHalfDepth());
	modelMatrix.rotateRzRyRx(0.0f, 0.0f, 0.0f);
	modelMatrix.scale(axisAlignedBox.getHalfWidth(), axisAlignedBox.getHalfHeight(), 0.0f);
	LineGeometryManager::getInstance()->getLineGeometry("Square")->draw(modelMatrix, color);

	// Top
	modelMatrix.identity();
	modelMatrix.translate(axisAlignedBox.getCenter().getX(), axisAlignedBox.getCenter().getY(), axisAlignedBox.getCenter().getZ());
	modelMatrix.translate(0.0f, axisAlignedBox.getHalfHeight(), 0.0f);
	modelMatrix.rotateRzRyRx(0.0f, 0.0f, 90.0f);
	modelMatrix.scale(axisAlignedBox.getHalfWidth(), axisAlignedBox.getHalfDepth(), 0.0f);
	LineGeometryManager::getInstance()->getLineGeometry("Square")->draw(modelMatrix, color);

	// Bottom
	modelMatrix.identity();
	modelMatrix.translate(axisAlignedBox.getCenter().getX(), axisAlignedBox.getCenter().getY(), axisAlignedBox.getCenter().getZ());
	modelMatrix.translate(0.0f, -axisAlignedBox.getHalfHeight(), 0.0f);
	modelMatrix.rotateRzRyRx(0.0f, 0.0f, 90.0f);
	modelMatrix.scale(axisAlignedBox.getHalfWidth(), axisAlignedBox.getHalfDepth(), 0.0f);
	LineGeometryManager::getInstance()->getLineGeometry("Square")->draw(modelMatrix, color);

	// Left and Right not needed
}

void DebugDraw::draw(const Plane& plane, const Point4& origin, const Color& color) const
{
	Matrix4x4 modelMatrix;

	if (!LineGeometryManager::getInstance()->getLineGeometry("GridPlane").get())
	{
		return;
	}

	float x = -plane.getPlane()[0] * plane.getPlane()[3] + origin.getX();
	float y = -plane.getPlane()[1] * plane.getPlane()[3] + origin.getY();
	float z = -plane.getPlane()[2] * plane.getPlane()[3] + origin.getZ();

	modelMatrix.identity();
	modelMatrix.translate(x, y, z);
	modelMatrix.rotateRzRyRx(0.0f, plane.getPlane()[0] * 90.0f, plane.getPlane()[1] * -90.0f);

	glDisable(GL_CULL_FACE);
	LineGeometryManager::getInstance()->getLineGeometry("GridPlane")->draw(modelMatrix, color);
	glEnable(GL_CULL_FACE);
}

void DebugDraw::drawSphere(const Point4& position, const Vector3& offset, float radius, const Color& color) const
{
	Matrix4x4 modelMatrix;

	if (!LineGeometryManager::getInstance()->getLineGeometry("Sphere").get())
	{
		return;
	}

	modelMatrix.identity();
	modelMatrix.translate(position.getX() + offset.getX(), position.getY() + offset.getY(), position.getZ() + offset.getZ());
	modelMatrix.scale(radius * 2.0f, radius * 2.0f, radius * 2.0f);
	glEnable(GL_CULL_FACE);
	LineGeometryManager::getInstance()->getLineGeometry("Sphere")->draw(modelMatrix, color);
}

void DebugDraw::drawCone(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfExtend, float radius, const Color& color) const
{
	Matrix4x4 modelMatrix;

	if (!LineGeometryManager::getInstance()->getLineGeometry("Cone").get())
	{
		return;
	}

	modelMatrix.identity();
	modelMatrix.translate(position.getX(), position.getY(), position.getZ());
	modelMatrix.multiply(rotation.getRotationMatrix4x4());
	modelMatrix.translate(offset.getX(), offset.getY(), offset.getZ());
	modelMatrix.scale(radius * 2.0f, halfExtend * 2.0f, radius * 2.0f);
	glEnable(GL_CULL_FACE);
	LineGeometryManager::getInstance()->getLineGeometry("Cone")->draw(modelMatrix, color);
}

void DebugDraw::drawCylinder(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfExtend, float radius, const Color& color) const
{
	Matrix4x4 modelMatrix;

	if (!LineGeometryManager::getInstance()->getLineGeometry("Cylinder").get())
	{
		return;
	}

	modelMatrix.identity();
	modelMatrix.translate(position.getX(), position.getY(), position.getZ());
	modelMatrix.multiply(rotation.getRotationMatrix4x4());
	modelMatrix.translate(offset.getX(), offset.getY(), offset.getZ());
	modelMatrix.scale(radius * 2.0f, halfExtend * 2.0f, radius * 2.0f);
	glEnable(GL_CULL_FACE);
	LineGeometryManager::getInstance()->getLineGeometry("Cylinder")->draw(modelMatrix, color);
}

void DebugDraw::drawArrow(const Point4& position, const Vector3& offset, const Quaternion& rotation, float lengthTail, float radiusTail, float lengthHead, float radiusHead, const Color& color) const
{
	drawCylinder(position, offset, rotation, lengthTail* 0.5f, radiusTail, color);
	drawCone(position, offset + Vector3(0.0f, lengthTail * 0.5f + lengthHead * 0.5f, 0.0f), rotation, lengthHead * 0.5f, radiusHead, color);
}

void DebugDraw::drawPyramid(const Point4& position, const Vector3& offset, const Quaternion& rotation, float halfWidth, float halfDepth, float halfHeight, const Color& color) const
{
	Matrix4x4 modelMatrix;

	if (!LineGeometryManager::getInstance()->getLineGeometry("Pyramid").get())
	{
		return;
	}

	modelMatrix.identity();
	modelMatrix.translate(position.getX(), position.getY(), position.getZ());
	modelMatrix.multiply(rotation.getRotationMatrix4x4());
	modelMatrix.translate(offset.getX(), offset.getY(), offset.getZ());
	modelMatrix.scale(halfWidth * 2.0f, halfHeight * 2.0f, halfDepth * 2.0f);
	glEnable(GL_CULL_FACE);
	LineGeometryManager::getInstance()->getLineGeometry("Pyramid")->draw(modelMatrix, color);
}

