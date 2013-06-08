/*
 * ProgramFactory.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef PROGRAMFACTORY_H_
#define PROGRAMFACTORY_H_

#include "../../UsedLibs.h"

#include "Program.h"

class ProgramFactory
{

private:

	static std::string path;

public:
	ProgramFactory();
	virtual ~ProgramFactory();

	static const std::string& getPath();

	static void setPath(const std::string& path);

	ProgramSP createPhongProgram() const;

	ProgramSP createPhongRenderToCubeMapProgram() const;

	ProgramSP createPhongRenderToShadowMapProgram() const;

	ProgramSP createFontProgram() const;

	ProgramSP createPostProcess2DProgram() const;

	ProgramSP createLineGeometryProgram() const;

	ProgramSP createLineGeometryLinesProgram() const;

	ProgramSP createSkyProgram() const;

	ProgramSP createGroundProgram() const;

	ProgramSP createGroundRenderToCubeMapProgram() const;

	ProgramSP createGroundRenderToShadowMapProgram() const;

};

#endif /* PROGRAMFACTORY_H_ */
