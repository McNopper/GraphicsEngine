/*
 * ProgramFactory.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef PROGRAMFACTORY_H_
#define PROGRAMFACTORY_H_

#include "Program.h"

class ProgramFactory
{
public:
	ProgramFactory();
	virtual ~ProgramFactory();

	ProgramSP createPhongProgram() const;

	ProgramSP createPhongRenderToCubeMapProgram() const;

	ProgramSP createFontProgram() const;

	ProgramSP createPostProcess2DProgram() const;

	ProgramSP createLineGeometryProgram() const;

	ProgramSP createLineGeometryLinesProgram() const;

	ProgramSP createSkyProgram() const;

};

#endif /* PROGRAMFACTORY_H_ */
