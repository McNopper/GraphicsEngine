/*
 * LineGeometryManager.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef LINEGEOMETRYMANAGER_H_
#define LINEGEOMETRYMANAGER_H_

#include "../../UsedLibs.h"

#include "LineGeometry.h"

class LineGeometryManager {
private:

	static LineGeometryManager* instance;

	std::map<std::string, LineGeometrySP> allLineGeometries;

	LineGeometryManager();
	virtual ~LineGeometryManager();

public:

	static LineGeometryManager* getInstance();

	static void terminate();

	bool containsLineGeometry(const std::string& key) const;

	const LineGeometrySP& getLineGeometry(const std::string& key) const;

	void setLineGeometry(const std::string& key, const LineGeometrySP& lineGeometry);

};

#endif /* LINEGEOMETRYMANAGER_H_ */
