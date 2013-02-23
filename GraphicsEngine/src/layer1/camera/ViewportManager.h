/*
 * ViewportManager.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef VIEWPORTMANAGER_H_
#define VIEWPORTMANAGER_H_

#include "../../UsedLibs.h"

#include "Viewport.h"

class ViewportManager
{

private:

	static ViewportManager* instance;

	std::map<std::string, ViewportSP> allViewports;

public:

	static const std::string DEFAULT_VIEWPORT_KEY;

private:

	ViewportManager();
	virtual ~ViewportManager();

public:

	static ViewportManager* getInstance();

	static void terminate();

	const ViewportSP& getDefaultViewport() const;

	bool containsViewport(const std::string& key) const;

	const ViewportSP& getViewport(const std::string& key) const;

	void setViewport(const std::string& key, const ViewportSP& viewport);

};

#endif /* VIEWPORTMANAGER_H_ */
