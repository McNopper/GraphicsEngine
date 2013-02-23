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
		LineGeometryManager::getInstance()->getLineGeometry("Sphere")->draw(modelMatrix, color);
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
