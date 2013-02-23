/*
 * SkyManager.h
 *
 *  Created on: 18.11.2012
 *      Author: nopper
 */

#ifndef SKYMANAGER_H_
#define SKYMANAGER_H_

#include "../../UsedLibs.h"

#include "Sky.h"

class SkyManager
{

private:

	static SkyManager* instance;

	std::map<std::string, SkySP> allSkies;

	SkySP activeSky;

	SkyManager();
	virtual ~SkyManager();

public:

	static SkyManager* getInstance();

	static void terminate();

	const SkySP& getSky(const std::string& key) const;

	void setSky(const std::string& key, const SkySP& sky);

	const SkySP& getActiveSky() const;

	void setActiveSky(const std::string& key);

	void resetActiveSky();

	bool hasActiveSky() const;

	void setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const;

};

#endif /* SKYMANAGER_H_ */
