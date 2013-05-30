/*
 * LightManager.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include "../../UsedLibs.h"

#include "Light.h"

class LightManager
{

private:

	static LightManager* instance;

	std::map<std::string, LightSP> allLights;

	Color ambientLightColor;

	LightManager();
	virtual ~LightManager();

public:

	static const std::string DEFAULT_DIRECTIONAL_LIGHT_KEY;

	static LightManager* getInstance();

	static void terminate();

	bool containsLight(const std::string& key) const;

	const LightSP& getLight(const std::string& key) const;

	const LightSP& getDefaultDirectionalLight() const;

	void setLight(const std::string& key, const LightSP& light);

	const Color& getAmbientLightColor() const;

	void setAmbientLightColor(const Color& ambientLightColor);

};

#endif /* LIGHTMANAGER_H_ */
