/*
 * ProgramManagerProxy.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef PROGRAMMANAGERPROXY_H_
#define PROGRAMMANAGERPROXY_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"

class ProgramManagerProxy
{

private:

	ProgramManagerProxy();
	~ProgramManagerProxy();

public:

	static void setLightByType(const std::string& programType, const LightSP& light);

	static void setLightsByType(const std::string& programType, const std::vector<LightSP>& lights);

	static void setCameraByType(const std::string& programType, const CameraSP& camera);

};

#endif /* PROGRAMMANAGERPROXY_H_ */
