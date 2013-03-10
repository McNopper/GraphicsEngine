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
	glusCreateSpheref(&sphere, 1.0f, 32);
	lineGeometry = LineGeometrySP(new LineGeometry(sphere));
	glusDestroyShapef(&sphere);
	LineGeometryManager::getInstance()->setLineGeometry("Sphere", lineGeometry);

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
