/*
 * LightManager.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Light.h"

class LightManager : public Singleton<LightManager>
{

	friend class Singleton<LightManager>;

private:

	KeyValueMap<std::string, LightSP> allLights;

	Color ambientLightColor;

	LightManager();
	virtual ~LightManager();

public:

	static const std::string DEFAULT_DIRECTIONAL_LIGHT_KEY;

	bool containsLight(const std::string& key) const;

	const LightSP& getLight(const std::string& key) const;

	const LightSP& getDefaultDirectionalLight() const;

	void setLight(const std::string& key, const LightSP& light);

	const Color& getAmbientLightColor() const;

	void setAmbientLightColor(const Color& ambientLightColor);

};

#endif /* LIGHTMANAGER_H_ */
