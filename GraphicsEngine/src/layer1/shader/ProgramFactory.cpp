/*
 * ProgramFactory.cpp
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#include "ProgramManager.h"

#include "ProgramFactory.h"

using namespace std;

string ProgramFactory::path = "../GraphicsEngine/shader/";

ProgramFactory::ProgramFactory()
{
}

ProgramFactory::~ProgramFactory()
{
}

ProgramSP ProgramFactory::createPhongProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "Phong.vert.glsl", path + "Phong.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createPhongRenderToCubeMapProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexGeometryFragmentProgramBy(path + "PhongToCubeMap.vert.glsl", path + "PhongToCubeMap.geom.glsl", path + "Phong.frag.glsl", ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE);

	return program;
}

ProgramSP ProgramFactory::createPhongRenderToShadowMapProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "Phong.vert.glsl", path + "Red.frag.glsl", ProgramManager::RENDER_TO_SHADOWMAP_PROGRAM_TYPE);

	return program;
}

ProgramSP ProgramFactory::createFontProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "Font.vert.glsl", path + "Font.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createPostProcess2DProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "PostProcess.vert.glsl", path + "PostProcess.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createLineGeometryProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "LineGeometry.vert.glsl", path + "LineGeometry.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createLineGeometryLinesProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "LineGeometryLines.vert.glsl", path + "LineGeometry.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createSkyProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexFragmentProgramBy(path + "Sky.vert.glsl", path + "Sky.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createGroundProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexControlEvaluateGeometryFragmentProgramBy(path + "Ground.vert.glsl", path + "Ground.cont.glsl", path + "Ground.eval.glsl", path + "Ground.geom.glsl", path + "Phong.frag.glsl");

	return program;
}

ProgramSP ProgramFactory::createGroundRenderToCubeMapProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexControlEvaluateGeometryFragmentProgramBy(path + "Ground.vert.glsl", path + "Ground.cont.glsl", path + "Ground.eval.glsl", path + "GroundToCubeMap.geom.glsl", path + "Phong.frag.glsl", ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE);

	return program;
}

ProgramSP ProgramFactory::createGroundRenderToShadowMapProgram() const
{
	ProgramSP program;

	program = ProgramManager::getInstance()->getVertexControlEvaluateGeometryFragmentProgramBy(path + "Ground.vert.glsl", path + "Ground.cont.glsl", path + "Ground.eval.glsl", path + "Ground.geom.glsl", path + "Red.frag.glsl", ProgramManager::RENDER_TO_SHADOWMAP_PROGRAM_TYPE);

	return program;
}

const string& ProgramFactory::getPath()
{
	return path;
}

void ProgramFactory::setPath(const string& path)
{
	ProgramFactory::path = path;
}
