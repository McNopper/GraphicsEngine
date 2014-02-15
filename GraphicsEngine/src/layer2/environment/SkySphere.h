/*
 * SkySphere.h
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#ifndef SKYSPHERE_H_
#define SKYSPHERE_H_

#include "Sky.h"

class SkySphere : public Sky
{

public:

	SkySphere(float radiusX, float radiusY, float radiusZ, const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);
	SkySphere(float radiusX, float radiusY, float radiusZ, const std::string& filename);
	virtual ~SkySphere();
};

#endif /* SKYSPHERE_H_ */
