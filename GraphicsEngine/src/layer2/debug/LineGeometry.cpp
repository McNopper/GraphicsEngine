/*
 * LineGeometry.cpp
 *
 *  Created on: 17.09.2012
 *      Author: nopper
 */

#include "../../layer1/shader/ProgramFactory.h"
#include "../../layer1/shader/Variables.h"

#include "LineGeometry.h"

LineGeometry::LineGeometry(const GLUSline& lineGeometry) :
		mode(lineGeometry.mode)
{
	ProgramFactory programFactory;
	program = programFactory.createLineGeometryProgram();

	numberIndices = lineGeometry.numberIndices;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER,
			lineGeometry.numberVertices * 4 * sizeof(GLfloat),
			(GLfloat*) lineGeometry.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			lineGeometry.numberIndices * sizeof(GLuint),
			(GLuint*) lineGeometry.indices, GL_STATIC_DRAW);

	drawVAO = LineGeometryVAOSP(new LineGeometryVAO(program, *this));

	//

	programLines = programFactory.createLineGeometryLinesProgram();

	drawLinesVAO = LineGeometryVAOSP(new LineGeometryVAO(programLines, *this));
}

LineGeometry::LineGeometry(const GLUSshape& shapeGeometry) :
	mode(shapeGeometry.mode)
{
	ProgramFactory programFactory;
	program = programFactory.createLineGeometryProgram();

	numberIndices = shapeGeometry.numberIndices;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER,
			shapeGeometry.numberVertices * 4 * sizeof(GLfloat),
			(GLfloat*) shapeGeometry.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			shapeGeometry.numberIndices * sizeof(GLuint),
			(GLuint*) shapeGeometry.indices, GL_STATIC_DRAW);

	drawVAO = LineGeometryVAOSP(new LineGeometryVAO(program, *this));

	//

	programLines = programFactory.createLineGeometryLinesProgram();

	drawLinesVAO = LineGeometryVAOSP(new LineGeometryVAO(programLines, *this));
}

LineGeometry::~LineGeometry()
{
	glDeleteBuffers(1, &vboVertices);

	glDeleteBuffers(1, &vboIndices);

	drawVAO.reset();

	program.reset();

	drawLinesVAO.reset();

	programLines.reset();

}

GLuint LineGeometry::getVboVertices() const
{
	return vboVertices;
}

GLuint LineGeometry::getVboIndices() const
{
	return vboIndices;
}

void LineGeometry::draw(const Matrix4x4& modelMatrix, const Color& color) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	program->use();

	glUniformMatrix4fv(program->getUniformLocation(u_modelMatrix), 1, GL_FALSE,
			modelMatrix.getM());
	glUniform4fv(program->getUniformLocation(u_lineGeometryColor), 1,
			color.getRGBA());

	drawVAO->bind();

	glDrawElements(mode, numberIndices, GL_UNSIGNED_INT, 0);

	drawVAO->unbind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LineGeometry::drawLines(const Matrix4x4& modelMatrix, const Point4& offset0, const Point4& offset1, const Color& color) const
{
	Vector3 vector0 = offset0 - Point4();
	Vector3 vector1 = offset1 - Point4();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	programLines->use();

	glUniformMatrix4fv(programLines->getUniformLocation(u_modelMatrix), 1, GL_FALSE,
			modelMatrix.getM());
	glUniform4fv(programLines->getUniformLocation(u_lineGeometryColor), 1,
			color.getRGBA());

	glUniform3fv(programLines->getUniformLocation(u_lineGeometryOffset0), 1,
			vector0.getV());
	glUniform3fv(programLines->getUniformLocation(u_lineGeometryOffset1), 1,
			vector1.getV());

	drawLinesVAO->bind();

	glDrawElements(GL_LINES, numberIndices, GL_UNSIGNED_INT, 0);

	drawLinesVAO->unbind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
