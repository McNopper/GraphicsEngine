/*
 * SkyVAO.h
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#ifndef SKYVAO_H_
#define SKYVAO_H_

#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/VAO.h"

class Sky;

class SkyVAO : public VAO
{
public:
	SkyVAO(const ProgramSP& program, const Sky& sky);
	virtual ~SkyVAO();
};

typedef std::shared_ptr<SkyVAO> SkyVAOSP;

#endif /* SKYVAO_H_ */
