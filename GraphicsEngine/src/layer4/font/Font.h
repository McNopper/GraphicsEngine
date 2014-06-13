/*
 * Font.h
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#ifndef FONT_H_
#define FONT_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer1/shader/Program.h"
#include "../../layer3/camera/Camera.h"
#include "FontVAO.h"

class Font
{

private:

	float width;
	float height;
	std::int32_t columns;
	std::int32_t rows;
	float cellWidth;
	float cellWidthNormalized;
	float cellHeight;
	float cellHeightNormalized;
	float fontWidth;
	float fontHeight;

	GLuint fontTextureName;

	GLuint vboVertices;
	GLuint vboTexCoords;

	GLuint vboIndices;

	std::uint32_t numberIndices;

	CameraSP camera;

	ProgramSP program;

	FontVAOSP fontVAO;

	void internalPrint(float x, float y, const Color& color, const char* output) const;

public:

	Font(const std::string& filename, float width, float height, std::int32_t columns, std::int32_t rows, float cellWidth, float cellHeight, float fontWidth, float fontHeight);
	virtual ~Font();

	GLuint getVboVertices() const;
	GLuint getVboTexCoords() const;

	GLuint getVboIndices() const;

	void print(float x, float y, const Color& color, const char* output, ...) const;

	void print(float x, float y, const Color& color, const std::string& output) const;

};

typedef std::shared_ptr<Font> FontSP;

#endif /* FONT_H_ */
