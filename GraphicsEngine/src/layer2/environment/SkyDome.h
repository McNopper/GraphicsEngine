/*
 * SkyDome.h
 *
 *  Created on: 11.11.2012
 *      Author: nopper
 */

#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "Sky.h"

class SkyDome: public Sky
{

public:

	SkyDome(float radiusX, float radiusY, float radiusZ, const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);
	SkyDome(float radiusX, float radiusY, float radiusZ, const std::string& filename);
	virtual ~SkyDome();

};

#endif /* SKYDOME_H_ */
