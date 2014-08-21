/*
 * DebugDrawFactory.cpp
 *
 *  Created on: 21.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "LineGeometry.h"
#include "LineGeometryManager.h"

#include "DebugDrawFactory.h"

DebugDrawFactory::DebugDrawFactory()
{
}

DebugDrawFactory::~DebugDrawFactory()
{
}

void DebugDrawFactory::createDefaultDebugGeometry() const
{
	LineGeometrySP lineGeometry;

	GLUSline gridPlane;
	glusLineCreateRectangularGridf(&gridPlane, 50.0f, 50.0f, 50, 50);
	lineGeometry = LineGeometrySP(new LineGeometry(gridPlane));
	glusLineDestroyf(&gridPlane);
	LineGeometryManager::getInstance()->setLineGeometry("GridPlane", lineGeometry);

	GLUSshape sphere;
	glusShapeCreateSpheref(&sphere, 1.0f, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(sphere));
	glusShapeDestroyf(&sphere);
	LineGeometryManager::getInstance()->setLineGeometry("Sphere", lineGeometry);

	GLUSshape cone;
	glusShapeCreateConef(&cone, 0.5f, 0.5f, 16, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(cone));
	glusShapeDestroyf(&cone);
	LineGeometryManager::getInstance()->setLineGeometry("Cone", lineGeometry);

	GLUSshape pyramid;
	glusShapeCreateConef(&pyramid, 0.5f, 0.5f, 4, 1);

	// The pyramid gets rotated. So adjust the height to the edge and not the vertex.
	float height = sqrtf(0.125f);
	Matrix4x4 modelMatrix;
	modelMatrix.scale(0.5f / height, 1.0f, 0.5f / height);
	modelMatrix.rotateRzRyRx(0.0f, 45.0f, 0.0f);
	for (uint32_t i = 0; i < pyramid.numberVertices; i++)
	{
		glusMatrix4x4MultiplyPoint4f(&pyramid.vertices[i*4], modelMatrix.getM(), &pyramid.vertices[i*4]);
	}

	lineGeometry = LineGeometrySP(new LineGeometry(pyramid));
	glusShapeDestroyf(&pyramid);
	LineGeometryManager::getInstance()->setLineGeometry("Pyramid", lineGeometry);

	GLUSshape cylinder;
	glusShapeCreateCylinderf(&cylinder, 0.5f, 0.5f, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(cylinder));
	glusShapeDestroyf(&cone);
	LineGeometryManager::getInstance()->setLineGeometry("Cylinder", lineGeometry);

	GLUSline square;
	glusLineCreateSquaref(&square, 1.0f);
	lineGeometry = LineGeometrySP(new LineGeometry(square));
	glusLineDestroyf(&square);
	LineGeometryManager::getInstance()->setLineGeometry("Square", lineGeometry);

	GLUSline circle;
	glusLineCreateCirclef(&circle, 1.0f, 32);
	lineGeometry = LineGeometrySP(new LineGeometry(circle));
	glusLineDestroyf(&circle);
	LineGeometryManager::getInstance()->setLineGeometry("Circle", lineGeometry);

	GLUSline singleLine;
	GLUSfloat origin0[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLUSfloat origin1[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	glusLineCreateLinef(&singleLine, origin0, origin1);
	lineGeometry = LineGeometrySP(new LineGeometry(singleLine));
	glusLineDestroyf(&singleLine);
	LineGeometryManager::getInstance()->setLineGeometry("SingleLine", lineGeometry);
}
