/*
 * SpotLight.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "../../layer0/math/Vector3.h"

#include "PointLight.h"

class SpotLight: public PointLight
{

private:

	Vector3 spotDirection;
	float spotCosCutOff;
	float spotCosCutOffOuter;

public:
	SpotLight(const std::string& name, float spotCosCutOff, float spotCosCutOffOuter, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& diffuse,
			const Color& specular);
	virtual ~SpotLight();

	float getSpotCosCutOff() const;
	void setSpotCosCutOff(float spotCosCutOff);
	float getSpotCosCutOffOuter() const;
	void setSpotCosCutOffOuter(float spotCosCutOffOuter);

	virtual void setLightProperties(std::uint32_t lightNumber, const ProgramSP& program, const Point4& position, const Quaternion& rotation) const;

	virtual void debugDraw(const Point4& position, const Quaternion& rotation) const;

	virtual std::int32_t getShadowType() const;

};

typedef std::shared_ptr<SpotLight> SpotLightSP;

#endif /* SPOTLIGHT_H_ */
