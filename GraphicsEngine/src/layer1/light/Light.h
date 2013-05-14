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
#include "../../layer0/shader/Program.h"
#include "../../layer0/shader/Variables.h"

class Light
{

protected:

	Color ambient;
	Color diffuse;
	Color specular;

public:

	Light(const Color& ambient, const Color& diffuse, const Color& specular);
	virtual ~Light();

	const Color& getAmbient() const;
	void setAmbient(const Color& ambient);
	const Color& getDiffuse() const;
	void setDiffuse(const Color& diffuse);
	const Color& getSpecular() const;
	void setSpecular(const Color& specular);

	virtual void setLightProperties(boost::uint32_t lightNumber, const ProgramSP& program) const = 0;

};

typedef boost::shared_ptr<Light> LightSP;

#endif /* LIGHT_H_ */
