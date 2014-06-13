/*
 * LineGeometry.h
 *
 *  Created on: 17.09.2012
 *      Author: nopper
 */

#ifndef LINEGEOMETRY_H_
#define LINEGEOMETRY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Point4.h"
#include "../../layer1/shader/Program.h"
#include "LineGeometryVAO.h"

class LineGeometry
{

private:

	GLenum mode;

	GLuint vboVertices;

	GLuint vboIndices;

	std::uint32_t numberIndices;

	ProgramSP program;

	LineGeometryVAOSP drawVAO;

	ProgramSP programLines;

	LineGeometryVAOSP drawLinesVAO;

public:
	LineGeometry(const GLUSline& lineGeometry);
	LineGeometry(const GLUSshape& shapeGeometry);
	virtual ~LineGeometry();

	GLuint getVboVertices() const;

	GLuint getVboIndices() const;

	void draw(const Matrix4x4& modelMatrix, const Color& color) const;

	void drawLines(const Matrix4x4& modelMatrix, const Point4& offset0, const Point4& offset1, const Color& color) const;

};

typedef std::shared_ptr<LineGeometry> LineGeometrySP;

#endif /* LINEGEOMETRY_H_ */
