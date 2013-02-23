/*
 * FontVAO.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef FONTVAO_H_
#define FONTVAO_H_

#include "../../layer0/shader/Program.h"
#include "../../layer0/shader/VAO.h"

class Font;

class FontVAO : public VAO {
public:
	FontVAO(const ProgramSP& program, const Font& font);
	virtual ~FontVAO();
};

typedef boost::shared_ptr<FontVAO> FontVAOSP;

#endif /* FONTVAO_H_ */
