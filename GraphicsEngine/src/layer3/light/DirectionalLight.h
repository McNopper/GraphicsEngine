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

	Vector3 direction;

public:
	DirectionalLight(const std::string& name, const Color& diffuse,
			const Color& specular);
	virtual ~DirectionalLight();

	virtual void setLightProperties(std::uint32_t lightNumber, const ProgramSP& program, const Point4& position, const Quaternion& rotation) const;

	virtual void debugDraw(const Point4& position, const Quaternion& rotation) const;

	virtual std::int32_t getShadowType() const;

};

typedef std::shared_ptr<DirectionalLight> DirectionalLightSP;

#endif /* DIRECTIONALLIGHT_H_ */
