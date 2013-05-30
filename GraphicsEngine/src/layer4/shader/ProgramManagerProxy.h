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

	static void setLightByType(const std::string& programType, boost::int32_t index, const LightSP& light, const Point4& position, const Quaternion& rotation);

	static void setAmbientLightColorByType(const std::string& programType);

	static void setNumberLightsByType(const std::string& programType, boost::int32_t numberLights);

	static void setCameraByType(const std::string& programType, const CameraSP& camera, const Point4& position, const Quaternion& rotation, bool useLocation = false);

};

#endif /* PROGRAMMANAGERPROXY_H_ */
