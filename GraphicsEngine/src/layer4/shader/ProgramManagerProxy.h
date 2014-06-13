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
#include "../../layer3/shadow/ShadowMap2D.h"

class ProgramManagerProxy
{

private:

	ProgramManagerProxy();
	~ProgramManagerProxy();

public:

	static void setLightByType(const std::string& programType, std::int32_t index, const LightSP& light, const Point4& position, const Quaternion& rotation);

	static void setAmbientLightColorByType(const std::string& programType);

	static void setNumberLightsByType(const std::string& programType, std::int32_t numberLights);

	static void setCameraByType(const std::string& programType, const CameraSP& camera, const Point4& position, const Quaternion& rotation, bool useLocation = false);

	static void setNoShadowByType(const std::string& programType);

	static void setShadowByType(const std::string& programType, std::int32_t index, const ShadowMap2DSP& shadowMap, const Matrix4x4& shadowMatrix, std::int32_t shadowType);

	static void setCascadedShadowByType(const std::string& programType, std::int32_t index, const ShadowMap2DSP& shadowMap, const std::vector<Matrix4x4>& shadowMatrices, std::int32_t shadowType);

};

#endif /* PROGRAMMANAGERPROXY_H_ */
