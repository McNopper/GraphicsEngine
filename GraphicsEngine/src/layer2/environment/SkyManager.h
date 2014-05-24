/*
 * SkyManager.h
 *
 *  Created on: 18.11.2012
 *      Author: nopper
 */

#ifndef SKYMANAGER_H_
#define SKYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Sky.h"

class SkyManager : public Singleton<SkyManager>
{

	friend class Singleton<SkyManager>;

private:

	KeyValueMap<std::string, SkySP> allSkies;

	SkySP activeSky;

protected:

	SkyManager();
	virtual ~SkyManager();

public:

	const SkySP& getSky(const std::string& key) const;

	void setSky(const std::string& key, const SkySP& sky);

	const SkySP& getActiveSky() const;

	void setActiveSky(const std::string& key);

	void resetActiveSky();

	bool hasActiveSky() const;

	void setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const;

};

#endif /* SKYMANAGER_H_ */
