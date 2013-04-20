/*
 * ProgramFactory.cpp
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#include "ProgramManager.h"

#include "ProgramFactory.h"

using namespace std;

ProgramFactory::ProgramFactory()
{
}

ProgramFactory::~ProgramFactory()
{
}

ProgramSP ProgramFactory::createPhongProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/Phong.vert.glsl", "../GraphicsEngine/shader/Phong.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createPhongRenderToCubeMapProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexGeometryFragmentProgramBy("../GraphicsEngine/shader/PhongToCubeMap.vert.glsl", "../GraphicsEngine/shader/PhongToCubeMap.geom.glsl", "../GraphicsEngine/shader/Phong.frag.glsl", ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE);

	return program;
}

ProgramSP ProgramFactory::createFontProgram() const
{
	ProgramSP program;

	program
		= ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/Font.vert.glsl", "../GraphicsEngine/shader/Font.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createPostProcess2DProgram() const
{
	ProgramSP program;

	program
		= ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/PostProcess.vert.glsl", "../GraphicsEngine/shader/PostProcess.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createLineGeometryProgram() const
{
	ProgramSP program;

	program
		= ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/LineGeometry.vert.glsl", "../GraphicsEngine/shader/LineGeometry.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createLineGeometryLinesProgram() const
{
	ProgramSP program;

	program
		= ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/LineGeometryLines.vert.glsl", "../GraphicsEngine/shader/LineGeometry.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createSkyProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy("../GraphicsEngine/shader/Sky.vert.glsl", "../GraphicsEngine/shader/Sky.frag.glsl");

	return program;
}


