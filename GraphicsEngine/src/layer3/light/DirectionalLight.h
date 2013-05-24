/*
 * DirectionalLight.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "../../layer0/math/Vector3.h"

#include "Light.h"

class DirectionalLight: public Light
{

protected:

	Vector3 directionOrignal;
	Vector3 direction;

public:
	DirectionalLight(const Vector3& direction, const Color& ambient, const Color& diffuse,
			const Color& specular);
	virtual ~DirectionalLight();

	const Vector3& getDirection() const;
	void setDirection(const Vector3& direction);

	virtual void setRotation(const Quaternion& rotation);

	virtual void setPositionRotation(const Point4& position, const Quaternion& rotation);

	virtual void setLightProperties(boost::uint32_t lightNumber, const ProgramSP& program) const;

	virtual void debugDraw() const;

};

#endif /* DIRECTIONALLIGHT_H_ */
