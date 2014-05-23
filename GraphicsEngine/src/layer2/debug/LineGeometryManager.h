/*
 * LineGeometryManager.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef LINEGEOMETRYMANAGER_H_
#define LINEGEOMETRYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"

#include "LineGeometry.h"

class LineGeometryManager : public Singleton<LineGeometryManager>
{

	friend class Singleton<LineGeometryManager>;

private:

	std::map<std::string, LineGeometrySP> allLineGeometries;

	LineGeometryManager();
	virtual ~LineGeometryManager();

public:

	bool containsLineGeometry(const std::string& key) const;

	const LineGeometrySP& getLineGeometry(const std::string& key) const;

	void setLineGeometry(const std::string& key, const LineGeometrySP& lineGeometry);

};

#endif /* LINEGEOMETRYMANAGER_H_ */
