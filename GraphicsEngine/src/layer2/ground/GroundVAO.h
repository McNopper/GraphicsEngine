/*
 * GroundVAO.h
 *
 *  Created on: 17.05.2013
 *      Author: nopper
 */

#ifndef GROUNDVAO_H_
#define GROUNDVAO_H_

#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/VAO.h"

class Ground;

class GroundVAO : public VAO
{

public:

	GroundVAO(const ProgramSP& program, const Ground& ground);
	virtual ~GroundVAO();

	void update(const Ground& ground) const;

};

typedef std::shared_ptr<GroundVAO> GroundVAOSP;

#endif /* GROUNDVAO_H_ */
