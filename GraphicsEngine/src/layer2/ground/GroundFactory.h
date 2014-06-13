/*
 * GroundFactory.h
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#ifndef GROUNDFACTORY_H_
#define GROUNDFACTORY_H_

#include "../../UsedLibs.h"

#include "Ground.h"

class GroundFactory
{

public:

	GroundFactory();
	virtual ~GroundFactory();

	GroundSP createGround(float horizontalExtend, float verticalExtend, std::uint32_t rows, std::uint32_t columns) const;

};

#endif /* GROUNDFACTORY_H_ */
