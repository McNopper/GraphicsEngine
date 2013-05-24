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
	glusCreateRectangularGridf(&gridPlane, 50.0f, 50.0f, 50, 50);
	lineGeometry = LineGeometrySP(new LineGeometry(gridPlane));
	glusDestroyLinef(&gridPlane);
	LineGeometryManager::getInstance()->setLineGeometry("GridPlane", lineGeometry);

	GLUSshape sphere;
	glusCreateSpheref(&sphere, 1.0f, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(sphere));
	glusDestroyShapef(&sphere);
	LineGeometryManager::getInstance()->setLineGeometry("Sphere", lineGeometry);

	GLUSshape cone;
	glusCreateConef(&cone, 0.5f, 0.5f, 16, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(cone));
	glusDestroyShapef(&cone);
	LineGeometryManager::getInstance()->setLineGeometry("Cone", lineGeometry);

	GLUSshape pyramid;
	glusCreateConef(&pyramid, 0.5f, 0.5f, 4, 1);

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
	glusDestroyShapef(&pyramid);
	LineGeometryManager::getInstance()->setLineGeometry("Pyramid", lineGeometry);

	GLUSshape cylinder;
	glusCreateCylinderf(&cylinder, 0.5f, 0.5f, 16);
	lineGeometry = LineGeometrySP(new LineGeometry(cylinder));
	glusDestroyShapef(&cone);
	LineGeometryManager::getInstance()->setLineGeometry("Cylinder", lineGeometry);

	GLUSline square;
	glusCreateSquaref(&square, 1.0f);
	lineGeometry = LineGeometrySP(new LineGeometry(square));
	glusDestroyLinef(&square);
	LineGeometryManager::getInstance()->setLineGeometry("Square", lineGeometry);

	GLUSline circle;
	glusCreateCirclef(&circle, 1.0f, 32);
	lineGeometry = LineGeometrySP(new LineGeometry(circle));
	glusDestroyLinef(&circle);
	LineGeometryManager::getInstance()->setLineGeometry("Circle", lineGeometry);

	GLUSline singleLine;
	GLUSfloat origin0[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLUSfloat origin1[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	glusCreateLinef(&singleLine, origin0, origin1);
	lineGeometry = LineGeometrySP(new LineGeometry(singleLine));
	glusDestroyLinef(&singleLine);
	LineGeometryManager::getInstance()->setLineGeometry("SingleLine", lineGeometry);
}
