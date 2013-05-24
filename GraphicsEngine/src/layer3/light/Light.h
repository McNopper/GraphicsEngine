/*
 * Light.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Quaternion.h"
#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/Variables.h"

class Light
{

protected:

	Color ambient;
	Color diffuse;
	Color specular;

	Point4 position;
	Quaternion rotation;

public:

	Light(const Color& ambient, const Color& diffuse, const Color& specular);
	virtual ~Light();

	const Color& getAmbient() const;
	void setAmbient(const Color& ambient);
	const Color& getDiffuse() const;
	void setDiffuse(const Color& diffuse);
	const Color& getSpecular() const;
	void setSpecular(const Color& specular);

	virtual const Point4& getPosition() const;
	virtual void setPosition(const Point4& position);

	virtual const Quaternion& getRotation() const;
	virtual void setRotation(const Quaternion& rotation);

	virtual void setPositionRotation(const Point4& position, const Quaternion& rotation);

	virtual void setLightProperties(boost::uint32_t lightNumber, const ProgramSP& program) const = 0;

	virtual void debugDraw() const = 0;

};

typedef boost::shared_ptr<Light> LightSP;

#endif /* LIGHT_H_ */
