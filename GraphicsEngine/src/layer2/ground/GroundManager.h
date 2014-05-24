/*
 * GroundManager.h
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#ifndef GROUNDMANAGER_H_
#define GROUNDMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Ground.h"

class GroundManager : public Singleton<GroundManager>
{

	friend class Singleton<GroundManager>;

private:

	KeyValueMap<std::string, GroundSP> allGrounds;

	GroundManager();
	virtual ~GroundManager();

public:

	bool containsGroundByKey(const std::string& key) const;

	const GroundSP& getGroundByKey(const std::string& key) const;

	void setGround(const std::string& key, const GroundSP& ground);

};

#endif /* GROUNDMANAGER_H_ */
