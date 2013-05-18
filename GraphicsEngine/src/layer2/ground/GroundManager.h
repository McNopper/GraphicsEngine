/*
 * GroundManager.h
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#ifndef GROUNDMANAGER_H_
#define GROUNDMANAGER_H_

#include "../../UsedLibs.h"

#include "Ground.h"

class GroundManager
{
private:

	static GroundManager* instance;

	std::map<std::string, GroundSP> allGrounds;

	GroundManager();
	virtual ~GroundManager();

public:

	static GroundManager* getInstance();

	static void terminate();

	bool containsGroundByKey(const std::string& key) const;

	const GroundSP& getGroundByKey(const std::string& key) const;

	void setGround(const std::string& key, const GroundSP& ground);

};

#endif /* GROUNDMANAGER_H_ */
