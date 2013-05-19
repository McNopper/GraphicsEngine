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
	float spotExponent;

public:
	SpotLight(const Vector3& spotDirection, float spotCosCutOff, float spotCosCutOffOuter, float spotExponent, const Point4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& ambient, const Color& diffuse,
			const Color& specular);
	virtual ~SpotLight();

	float getSpotCosCutOff() const;
	void setSpotCosCutOff(float spotCosCutOff);
	float getSpotCosCutOffOuter() const;
	void setSpotCosCutOffOuter(float spotCosCutOffOuter);
	const Vector3& getSpotDirection() const;
	void setSpotDirection(const Vector3& spotDirection);
	float getSpotExponent() const;
	void setSpotExponent(float spotExponent);

	virtual void setLightProperties(boost::uint32_t lightNumber, const ProgramSP& program) const;

	virtual void setRotation(const Quaternion& rotation);

};

#endif /* SPOTLIGHT_H_ */
