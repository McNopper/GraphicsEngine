/*
 * PointLight.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "../../layer0/math/Geometry.h"
#include "../../layer0/math/Point4.h"

#include "Light.h"

class PointLight: public Light, public Geometry
{

protected:

	Point4 position;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

public:
	PointLight(const Point4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& ambient, const Color& diffuse,
			const Color& specular);
	virtual ~PointLight();

	const Point4& getPosition() const;
	void setPosition(const Point4& position);

	float getConstantAttenuation() const;
	void setConstantAttenuation(float constantAttenuation);
	float getLinearAttenuation() const;
	void setLinearAttenuation(float linearAttenuation);
	float getQuadraticAttenuation() const;
	void setQuadraticAttenuation(float quadraticAttenuation);

	virtual void setLightProperties(boost::uint32_t lightNumber, const ProgramSP& program) const;

	//

	virtual void updateLocation(const Point4& location);

	virtual void updateOrientation(const Quaternion& orientation);

	virtual void updateLocationOrientation(const Point4& location, const Quaternion& orientation);

};

#endif /* POINTLIGHT_H_ */
